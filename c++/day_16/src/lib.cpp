#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

#include "lib.hpp"

namespace aoc {

using InputType = std::unordered_map<std::string, std::pair<uint64_t, std::vector<std::string>>>;

void parse_inventory(InputType &readings, const std::string &inventory) {
    std::regex regex(R"R(Valve (\w+) has flow rate=(\d+); tunnels? leads? to valves? (?:(\w+), )*(\w+))R");
    std::stringstream stream(inventory);
    std::string line;
    std::smatch matches;
    while (std::getline(stream, line)) {
        if (std::regex_search(line, matches, regex)) {
            auto match = matches.begin();
            match++;

            const std::string name = *match;
            match++;

            const int flow = stoi(*match);
            match++;

            std::vector<std::string> tunnels;
            while(match < matches.cend()) {
                if(*match == "") goto ctn;
                tunnels.push_back(*match);
                ctn:;
                match++;
            }

            readings[name] = {flow, tunnels};
        } else {
            std::cout << "regex failed" << std::endl;
        }
    }
}

void calculate_connectivity_matrix(
    const InputType &readings, 
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> &next,
    std::unordered_map<std::string, std::unordered_map<std::string, uint64_t>> &dist
) {
    for(auto &[a, _] : readings) 
        for(auto &[b, __] : readings)
            dist[a][b] = 1000000; // close enough to infinity for us :-)
    
    for(auto &[u, data] : readings) {
        // for each node (u) do:
        dist[u][u] = 0;
        next[u][u] = u;
        auto &[flow, vs] = data;
        for( auto &v : vs) {
            // for each edge (u, v) do: 
            // dist[u][v] <- w(u, v) // the weight of the edge (u,v)
            dist[u][v] = 1;
            dist[v][u] = 1;
            // next[u][v] <- v
            next[u][v] = v;
            next[v][u] = v;
        }
    }

    for ( auto &[k, _] : readings )
        for ( auto &[i, __] : readings )
            for ( auto &[j, ___] : readings ) 
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
}

std::string stringify(std::unordered_map<std::string, bool> m) {
    std::string retval;
    for( auto &[k, v] : m) {
        retval.push_back(v ? 'T' : 'F');
    }
    return retval;
}

uint64_t find_max_pressure(
    const InputType &readings,
    const std::unordered_map<std::string, std::unordered_map<std::string, uint64_t>> &dist,
    const uint64_t &start_time,
    const uint64_t &end_time, 
    const std::string &curr,
    std::unordered_map<std::string, bool> &open
) {
    uint64_t max_pressure = 0;
    std::vector<std::string> max_valves;
    uint64_t time_to_next, next_pressure;
    
    for ( auto &[next, data]: readings ) {
        auto &[flow, _] = data;
        if (open[next]) continue; // skip if the valve is open
        
        time_to_next = dist.at(curr).at(next) + start_time + 1;
        if ( time_to_next > end_time) continue; // skip if we can't get there in time

        next_pressure = (end_time - time_to_next) * flow;
        
        open[next] = true;
        max_pressure = std::max(max_pressure, next_pressure + find_max_pressure(readings, dist, time_to_next, end_time, next, open));
        open[next] = false;
    }

    return max_pressure; 
}

int part_a(const std::string &inventory) {

    InputType readings;
    parse_inventory(readings, inventory);
    
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> next;
    std::unordered_map<std::string, std::unordered_map<std::string, uint64_t>> dist;
    calculate_connectivity_matrix(readings, next, dist);

    std::unordered_map<std::string, bool> open;
    for ( auto &[a, data] : readings) {
        auto &[flow, _] = data;
        open[a] = (flow == 0); // open all the valves with zero flow, cause they're useless
    }
    
    const auto &max_pressure = find_max_pressure(readings, dist, 0, 30, "AA", open);

    std::cout << max_pressure << std::endl;
    return max_pressure;
}

uint64_t find_max_pressure_2 (
    const InputType &readings,
    const std::unordered_map<std::string, std::unordered_map<std::string, uint64_t>> &dist,
    const uint64_t &me_start_time, 
    const std::string &me_curr,
    const uint64_t &elephant_start_time, 
    const std::string &elephant_curr,
    std::unordered_map<std::string, bool> &open
) {
    uint64_t max_pressure = 0;
    uint64_t time_to_next, next_pressure;

    for ( auto &[next, data]: readings ) {
        auto &[flow, _] = data;
        if (open[next]) continue; // skip if the valve is already open

        if( me_start_time <= elephant_start_time ) {
            time_to_next = dist.at(me_curr).at(next) + me_start_time + 1;
            if ( time_to_next > 26L ) continue; // skip if we can't get there in time

            next_pressure = (26L - time_to_next) * flow;
            
            open[next] = true;
            max_pressure = std::max(max_pressure, next_pressure + find_max_pressure_2(
                readings, dist, time_to_next, next, elephant_start_time, elephant_curr, open));
        }
        open[next] = false;
        
        // if me and the elephant are in the same place at the same time, we skip
        if( elephant_start_time < me_start_time || (elephant_start_time == me_start_time && me_curr != elephant_curr)) {
            time_to_next = dist.at(elephant_curr).at(next) + elephant_start_time + 1;
            if ( time_to_next > 26L ) continue; // skip if we can't get there in time

            next_pressure = (26L - time_to_next) * flow;
            
            open[next] = true;
            max_pressure = std::max(max_pressure, next_pressure + find_max_pressure_2(
                readings, dist, me_start_time, me_curr, time_to_next, next, open));
        }
        open[next] = false;
    }
    
    return max_pressure;
}

uint64_t part_b(const std::string &inventory) {
    InputType readings;
    parse_inventory(readings, inventory);
    
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> next;
    std::unordered_map<std::string, std::unordered_map<std::string, uint64_t>> dist;
    calculate_connectivity_matrix(readings, next, dist);

    std::unordered_map<std::string, bool> open;
    for ( auto &[a, data] : readings) {
        auto &[flow, _] = data;
        open[a] = (flow == 0); // open all the valves with zero flow, cause they're useless
    }
    
    int64_t max_pressure = find_max_pressure_2(readings, dist, 0, "AA", 0, "AA", open);

    return max_pressure;
}

} // namespace aoc