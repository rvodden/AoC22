#include <algorithm>
#include <deque>
#include <execution>
#include <iostream>
#include <map>
#include <mutex>
#include <numeric>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <queue>
#include <vector>

#include "lib.hpp"

namespace aoc {

enum Resource {
    ORE = 0,
    CLAY = 1,
    OBSIDIAN = 2,
    GEODE = 3,
};

std::ostream& operator<< (std::ostream &stream, const Resource &r) {
    switch(r) {
        case ORE:
            stream << "ORE";
            break;
        case CLAY:
            stream << "CLAY";
            break;
        case OBSIDIAN:
            stream << "OBSIDIAN";
            break;
        case GEODE:
            stream << "GEODE";
            break;
    }
    return stream;
}

const std::array<Resource, 4> resources = {ORE, CLAY, OBSIDIAN, GEODE};

class Blueprint {
  public:
    int id;
    std::array<std::array<int64_t, 4>, 4> costs;
    std::array<int64_t, 4>                limits;
    
    void                                  calculate_limits();

    std::array<int64_t, 4>                operator[]( const Resource &i ) const { return costs.at((int)i); };
};

void Blueprint::calculate_limits() {
    limits = {0,0,0,0};
    for(const auto &resource : resources) {
        for(const auto &robot_type : resources) {
            limits[resource] = std::max(limits[resource], costs[robot_type][resource]);
        }
    }
}

void print_blueprint(const Blueprint &blueprint) {
    for(const auto &robot_type : resources ) {
        std::cout << "A " << robot_type << " robot costs ";
        for(const auto &resource : resources ) {
            std::cout << blueprint[robot_type][resource] << " " << resource << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Limits are: " << std::endl;
    for(const auto& resource : resources) {
        std::cout << resource << " : " << blueprint.limits[resource] << " ";
    }
    std::cout << std::endl;
}

class State {
  public:
    explicit State(const int& minutes) : remaining_time(minutes) {};
    std::array<int64_t, 4> resources = { 0, 0, 0, 0 };
    std::array<int64_t, 4> robots    = { 1, 0, 0, 0 };
    int64_t remaining_time;

    bool operator==(const State &other) const {
        return remaining_time == other.remaining_time && 
            std::equal(resources.begin(), resources.end(), other.resources.begin()) &&
            std::equal(robots.begin(), robots.end(), other.robots.begin());
    }

};

class StateHash {
  public:
    std::size_t operator()(const State &state) const {
    std::size_t seed = 9;

    const auto &opp = [](const std::size_t &i, const std::size_t &s){ return i + 0x9e3779b9 + (s << 6) + (s >> 2); };

    for(auto& i : state.resources) {
        seed ^= opp(i, seed);
    }
    for(auto& i : state.robots) {
        seed ^= opp(i, seed);
    }
    seed ^= opp(state.remaining_time, seed);
    return seed;
    }
};

template<typename T>
class AtomicQueue
{
public:
    void push( const T& value )
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _queue.push(value);
    }

    T front()
    {
        return _queue.front();
    }

    void pop()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _queue.pop();
    }

    bool empty()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return _queue.empty();
    }

private:
    std::queue<T> _queue;
    mutable std::mutex _mutex;
};

using States = AtomicQueue<State>;

using InputType = std::vector<Blueprint>;

void parse_inventory(InputType &blueprints, const std::string &inventory) {

    std::regex regex(R"R(Blueprint (\d+): Each ore robot costs (\d+) ore. Each clay robot costs (\d+) ore. Each obsidian robot costs (\d+) ore and (\d+) clay. Each geode robot costs (\d+) ore and (\d+) obsidian.)R");
    std::stringstream stream(inventory);
    std::string line;
    std::smatch matches;
    Blueprint blueprint;
    
    while (std::getline(stream, line)) {
        if (std::regex_search(line, matches, regex)) {
            auto match = matches.begin();
            blueprint.id = std::stoi(*++match);

            blueprint.costs[ORE] = { unsigned(std::stoi(*++match)), 0, 0, 0 };
            blueprint.costs[CLAY] = { unsigned(std::stoi(*++match)), 0, 0, 0 };
            blueprint.costs[OBSIDIAN] = { unsigned(std::stoi(*++match)), unsigned(std::stoi(*++match)), 0, 0 };
            blueprint.costs[GEODE] = { unsigned(std::stoi(*++match)), 0, unsigned(std::stoi(*++match)), 0 };

            blueprint.calculate_limits();
            blueprints.push_back(blueprint);
        } else {
            std::cout << "regex failed" << std::endl;
        }
    }
}

void print_state(const State &state) {
    std::cout << "Remaining time: " << state.remaining_time << std::endl;
    std::cout << "Resources: ";
    for (auto &resource : resources) {
        std::cout << state.resources[resource] << ", ";
    }
    std::cout << std::endl;
    
    std::cout << "Robots ";
    for (auto &resource : resources) {
        std::cout << state.robots[resource] << ", ";
    }
    std::cout << std::endl;
}

int64_t time_to_robot(const Blueprint &blueprint, const State &state, const Resource &robot_type) {
    // std::cout << "Can we build a " << robot_type << " robot?" << std::endl;
    const auto& robot_cost = blueprint[robot_type];
    int64_t time = 0;
    int64_t t = 0;
    int64_t remaining_resource;
    for ( const auto &resource : resources ) {
        if( state.robots[resource] == 0  && robot_cost[resource] != 0 ) return -1;
        if( state.robots[resource] == 0  && robot_cost[resource] == 0 ) continue;
        remaining_resource = robot_cost[resource] - state.resources[resource];
        // std::cout << "We need to collect " << remaining_resource << " " << resource << ", ";
        t = (remaining_resource + state.robots[resource] - 1) / state.robots[resource]; // want ceil (x/y);
        // std::cout << "which will take " << t << " minutes." << std::endl;
        time = std::max(time, t);
    }
    // print_state(state);
    if (time >= 0) time += 1; // robots take a minute to build.
    // std::cout << "It will take " << time << " minutes to build a " << robot_type << " robot." << std::endl;
    return time;
}

void process_state(const Blueprint &blueprint, const State &state, States &states, int64_t &max_geodes) {
    // print_state(state);
    if ( state.remaining_time == 0 ) {
        // std::cout << "We're done and we decoded " << state.resources[GEODE] << " geodes." << std::endl << std::endl;
        max_geodes = std::max(max_geodes, state.resources[GEODE]);
        return;
    }

    if ( state.resources[GEODE] + state.remaining_time * state.robots[GEODE] +  state.remaining_time * (state.remaining_time) / 2 < max_geodes )
        return;

    bool built_a_robot = false;
    
    // See what happens if we buy each kind of robot
    for(const auto & robot_type : std::vector<Resource> { ORE, CLAY, OBSIDIAN, GEODE } ) {
        if ( blueprint.limits[robot_type] != 0 && state.robots[robot_type] >= blueprint.limits[robot_type] ) {
            // std::cout << "We've hit the limit and don't need to build any more " << robot_type << " robots." << std::endl;
            continue; // we can only build one robot in a minute
        }
        int64_t time = time_to_robot(blueprint, state, robot_type);
        if ( time < 0 ) {
            // std::cout << "We don't have the right robots to build a " << robot_type << " robot." << std::endl;
            continue; // not enough robots to build this kind of robot
        }
        if ( time > state.remaining_time ) {
            // std::cout << "We don't have enough time to build a " << robot_type << " robot. It will take " << time << " minutes." << std::endl;
            continue; // not enough time left to build the robot
        }
        
        State next = state;

        // std::cout << "We're going to build a " << robot_type << " robot. It will take " << time << " minutes." << std::endl;
        for (auto &resource : resources) {
            next.resources[resource] -= blueprint.costs[robot_type][resource]; // buy the robot
            next.resources[resource] += time * next.robots[resource]; // each robot mines 1 thing per turn
        }
        
        next.remaining_time -= time;
        next.robots[robot_type]++;
        
        // for (auto &resource : resources) {
        //     std::cout << "We are left with " << next.resources[resource] << " " << resource;
        //     std::cout << " and " << next.robots[resource] << " " << resource << " robots." << std::endl;
        // }
        states.push(next);
        built_a_robot = true;
    }

    if (!built_a_robot) {
        // std::cout << "We're not going to build a robot." << std::endl;
        State next = state;
        for (auto &resource : resources) {
            next.resources[resource] += state.robots[resource]; // each robot mines 1 thing per turn
        }
        next.remaining_time--;
        states.push(next);
    }
    // std::cout << std::endl;
}

int64_t process_blueprint(const Blueprint &blueprint, const int& minutes) {
    States states;
    int64_t max_geodes = 0;
    states.push(State(minutes));

    while(!states.empty()) {
        State state = states.front();
        states.pop();
        process_state(blueprint, state, states, max_geodes);
    }
    // std::cout << max_geodes << std::endl;
    return max_geodes;
}

int64_t part_a(const std::string &inventory) {
    std::vector<Blueprint> blueprints;
    parse_inventory(blueprints, inventory);


    std::vector<int64_t> results(blueprints.size());
    std::transform(std::execution::par, blueprints.begin(), blueprints.end(), results.begin(), [](const auto &b){ return process_blueprint(b, 24); });

    int64_t result = 0;
    for(uint16_t i = 1; i <= results.size(); i ++ ) {
        result += i * results[i-1];
    }

    return result;
}

int64_t part_b(const std::string &inventory) {
    std::vector<Blueprint> blueprints;
    parse_inventory(blueprints, inventory);


    std::vector<int64_t> results(3);
    std::transform(std::execution::par, blueprints.begin(), blueprints.begin() + 3, results.begin(), [](const auto &b){ return process_blueprint(b, 32); });

    int64_t result = 1;
    for(uint16_t i = 1; i <= results.size(); i ++ ) {
        result *= results[i-1];
    }

    return result;
}

} // namespace aoc