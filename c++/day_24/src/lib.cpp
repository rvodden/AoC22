#include <stdexcept>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <sstream>
#include <string>
#include <variant>
#include <regex>

#include "lib.hpp"

namespace aoc {


bool operator==(const Location &l, const Location &r) {
    return (l.first == r.first) && (l.second == r.second);
}

Location operator+(const Location &l, const Location &r) {
    return { l.first + r.first, l.second + r.second };
};

Location operator-(const Location &l, const Location &r) {
    return { l.first - r.first, l.second - r.second };
};

Location operator*(const Location &l, const int64_t &r) {
    return { l.first * r, l.second * r };
};

Location& operator+=(Location &l, const Location &r) {
    l.first += r.first;
    l.second += r.second;
    return l;
};

std::ostream& operator<<(std::ostream& s, const Location &l) {
    s << "(" << l.first << "," << l.second << ")";
    return s;
}

std::ostream& operator<<(std::ostream& s, const Bearing &b) {
    switch(b) {
        case Bearing::NORTH:
            s << '^';
            break;
        case Bearing::SOUTH:
            s << 'v';
            break;
        case Bearing::EAST:
            s << '>';
            break;
        case Bearing::WEST:
            s << '<';
            break;
        case Bearing::NONE:
            s << '#';
            break;
    }

    return s;
}

void State::print_map() const {
    for(const auto &y : std::ranges::views::iota(0, extents.second)) {
        for(const auto &x : std::ranges::views::iota(0, extents.first)) {
            const auto &[curr, end] = map.equal_range({x,y});
            if( curr == end ) {
                std::cout << ".";
                continue;
            }
            std::size_t distance = std::distance(curr, end);
            if( distance == 1) {
                std::cout << curr->second;
                continue;
            }
            std::cout << distance;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void State::print_map(const Location &location) const {
    for(const auto &y : std::ranges::views::iota(0, extents.second)) {
        for(const auto &x : std::ranges::views::iota(0, extents.first)) {
            if( location == Location {x,y}) {
                std::cout << "\033[1;37mE\033[0;m";
                continue;
            }
            const auto &[curr, end] = map.equal_range({x,y});
            if( curr == end ) {
                std::cout << ".";
                continue;
            }
            std::size_t distance = std::distance(curr, end);
            if( distance == 1) {
                std::cout << curr->second;
                continue;
            }
            std::cout << distance;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void wrap_around(const Location &extents, Location &location) {
    if(location.first >= extents.first - 1) location.first -= (extents.first - 2);
    if(location.second >= extents.second - 1) location.second -= (extents.second - 2);
    if(location.first < 1 ) location.first += (extents.first - 2);
    if(location.second < 1 ) location.second += (extents.second - 2);
}

void State::move() {
    Map new_map;
    Location new_location;
    for(const auto &[location, bearing] : map ) {
        new_location = location + NEIGHBOURS.at(bearing);
        if(bearing != Bearing::NONE) wrap_around(extents, new_location);
        new_map.insert({new_location, bearing});
    }
    map = new_map;
}

Location parse_input(Map &map, const std::string &input){
    std::stringstream stream(input);
    std::string line;
    uint64_t y = 0;
    uint64_t x = 0;
    while(std::getline(stream, line)) {
        x = 0;
        for (const auto &c : line) {
            switch(c) {
              case ' ':
              case '.':
                break;
              case '>':
                map.emplace(Location{x,y}, Bearing::EAST);
                break;
              case 'v':
                map.emplace(Location{x,y}, Bearing::SOUTH);
                break;
              case '<':
                map.emplace(Location{x,y}, Bearing::WEST);
                break;
              case '^':
                map.emplace(Location{x,y}, Bearing::NORTH);
                break;
              case '#':
                map.emplace(Location{x,y}, Bearing::NONE);
                break;
              default:
                std::cout << (int) c << std::endl;
                std::cout << c << std::endl;
                throw std::runtime_error("Invalid character.");
            }
            x++;
        }
        y++;
    }
    return {x, y};
}

bool in_bounds(const Location &extents, const Location &location) {
    if( location == Location{1,0} or location == extents + Location{-2, -1}) return true;
    return location.first >= 1 && location.first < extents.first - 1 && location.second >= 1 && location.second < extents.second - 1;
}

TemporalStepSet next_steps(const State &state, const TemporalLocation &location) {
    TemporalStepSet next_steps;
    Location next_step;
    for(const auto&[_, n] : NEIGHBOURS) {
        next_step = location.first + n;
        if (!in_bounds(state.extents, next_step)) continue;
        if (state.map.contains(next_step)) continue; // cannot sit on a blizzard;
        next_steps.insert({next_step, location.second + 1});
    }
    next_steps.insert({ location.first, location.second + 1 });
    return next_steps;
}

struct GScore {
    public:
        int64_t& operator[](const TemporalLocation &t) { return _gscore[t]; };
        int64_t get(const TemporalLocation &t) {
            try {
                return _gscore.at(t);
            } catch (std::out_of_range &e) {
                return std::numeric_limits<int64_t>::max();
            }
        } 
    private:
        std::unordered_map<TemporalLocation, int64_t, PairPairHash> _gscore;
};

int64_t path_length(const std::vector<State> &states, const int64_t &loop, const TemporalLocation &start, const Location &destination) {
    const auto &compare = [&destination](const TemporalLocation &l, const TemporalLocation &r) { 
        const auto &[x1, y1] = destination - l.first;
        const auto &[x2, y2] = destination - r.first;
        return (std::abs(x1) + std::abs(y1)) > (std::abs(x2) + std::abs(y2));
    };

    std::priority_queue<TemporalLocation, std::vector<TemporalLocation>, decltype(compare)> open_set(compare);
    std::unordered_map<TemporalLocation, TemporalLocation, PairPairHash> previous_step;
    GScore gscore;

    open_set.push(start);
    gscore[start] = 0;
    int64_t answer = -1;

    while(!open_set.empty()) {
        auto current = open_set.top();
        int64_t state_number = current.second % loop;
        if( state_number < 0 ) state_number += loop;
        const auto &current_state = states.at(state_number);

        std::cout << "Step " << current.second << ": " << std::endl;
        current_state.print_map(current.first);

        if(current.first == destination) {
            // current_state.print_map(current.first);
            answer =  gscore.get(current);
            break;
        }
        
        open_set.pop();
        auto ns = next_steps(current_state, current);
        for(const auto& neighbour : ns) {
            if (gscore.get(current) + 1 < gscore.get(neighbour) ) { // if its easier to get to the next_step via current
                previous_step[neighbour] = current;
                gscore[neighbour] = gscore.get(current) + 1;
                open_set.push(neighbour);
            }
        }
    }
    return answer;
}

void calculate_states(std::vector<State> &states, int64_t &loop, const State &state) {
    State local_state = state;
    loop = std::lcm(state.extents.first, state.extents.second);
    for ( int64_t i = 0; i < loop; i++) {
        states.push_back(local_state);
        local_state.move();
    }
}

int part_a(const std::string &input) {
    Map map;
    Location extents = parse_input(map, input);

    State state(map, extents);

    std::vector<State> states;
    int64_t loop;
    calculate_states(states, loop, state);
    
    TemporalLocation start = {{1,0}, 1};
    Location destination = extents + Location {-2,-1};
    int64_t answer = path_length(states, loop, start, destination);

    return answer;
}

int part_b(const std::string &input) {
    Map map;
    Location extents = parse_input(map, input);

    State state(map, extents);

    Location entrance = {1,0};
    Location exit = extents + Location {-2, -1};

    std::vector<State> states;
    int64_t loop;
    calculate_states(states, loop, state);
    
    TemporalLocation start = {entrance, 0};
    Location destination = exit;
    int64_t answer = path_length(states, loop, start, destination);

    start = {exit, answer};
    destination = entrance;
    answer += path_length(states, loop, start, destination);
    
    start = {entrance, answer};
    destination = extents + Location {-2, -1};
    answer += path_length(states, loop, start, destination);

    return answer;
}

} // namespace aoc