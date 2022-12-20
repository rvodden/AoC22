#include <bitset>
#include <string>
#include <deque>
#include <iostream>
#include <vector>

#include "lib.hpp"

namespace aoc {


Location operator+(const Location &l, const Location &r) {
    return { 
        std::get<0>(l) + std::get<0>(r),
        std::get<1>(l) + std::get<1>(r),
        std::get<2>(l) + std::get<2>(r)
    };
}

Location min(const Location &l, const Location &r) {
    return std::make_tuple(
        std::min(std::get<0>(l), std::get<0>(r)),
        std::min(std::get<1>(l), std::get<1>(r)),
        std::min(std::get<2>(l), std::get<2>(r))
    );
}

Location max(const Location &l, const Location &r) {
    return std::make_tuple(
        std::max(std::get<0>(l), std::get<0>(r)),
        std::max(std::get<1>(l), std::get<1>(r)),
        std::max(std::get<2>(l), std::get<2>(r))
    );
}


std::array<Location, 6> neighbours(const Location &l) {
    return {
        l + std::make_tuple( 1,  0,  0 ),
        l + std::make_tuple(-1,  0,  0 ),
        l + std::make_tuple( 0,  1,  0 ),
        l + std::make_tuple( 0, -1,  0 ),
        l + std::make_tuple( 0,  0,  1 ),
        l + std::make_tuple( 0,  0, -1 )
    };
}

int count_unoccupied_neighbours(const Locations &locations, const Location &l) {
    int count = 0;
    for(auto &n : neighbours(l)) {
        if (locations.contains(n)) continue;
        count++;
    }
    return count;
}

void parse_inventory(
        std::unordered_set<Location, LocationHash> &locations,
        const std::string &inventory
) {
    std::stringstream stream(inventory);
    std::string line;
    std::string number;
    std::array<int, 3> numbers;
    while(std::getline(stream, line)) {
        if(line == "") continue;
        auto s = line.begin();
        for(int i = 0; i < 3; i++) {
            auto t = std::find(s, line.end(), ',');
            number = std::string(s, t);
            numbers[i] = std::stoi(number);
            s = t + 1;
        }
        locations.insert({numbers[0], numbers[1], numbers[2]});
    }
}

void get_solid(Locations &locations, const Location &location, Locations &solid) {
    if(!locations.contains(location)) return;
    if(solid.contains(location)) return;
    
    solid.insert(location);

    for( auto &neighbour : neighbours(location) ) {
        get_solid(locations, neighbour, solid);
    }
    
    locations.erase(location);
}

void get_bounds_of_solid(const Locations &solid, Location &upper, Location &lower) {
    upper = std::make_tuple(0,0,0);
    lower = std::make_tuple(std::numeric_limits<int>::max(),std::numeric_limits<int>::max(),std::numeric_limits<int>::max());

    for (const auto &l : solid) {
        upper = max(l, upper);
        lower = min(l, lower);
    }
}

bool is_out_of_bounds(std::pair<Location, Location> bounds, const Location &l){
    auto &[lower, upper] = bounds;
    return 
        std::get<0>(upper) < std::get<0>(l) or std::get<0>(lower) > std::get<0>(l) or
        std::get<1>(upper) < std::get<1>(l) or std::get<1>(lower) > std::get<1>(l) or
        std::get<2>(upper) < std::get<2>(l) or std::get<2>(lower) > std::get<2>(l);
}


bool can_escape(const Locations &solid, const Location &location, const std::pair<Location, Location> &bounds, Locations &visited ) {
    if (visited.contains(location)) return false;
    if (solid.contains(location)) return false;
    visited.insert(location);

    if (is_out_of_bounds(bounds, location)) return true;

    const auto &ns = neighbours(location);
    return std::any_of(ns.begin(), ns.end(), [&solid, &bounds, &visited](const auto &l) { 
        return can_escape(solid, l, bounds, visited); 
    });
}


void fill_in_solid(Locations &solid) {
    Location upper, lower;
    get_bounds_of_solid(solid, upper, lower);
    std::pair<Location, Location> bounds(lower, upper);
    Locations visited, internal;

    for( const auto &s : solid ) {
        for(const auto &n : neighbours(s)) {
            if(!can_escape(solid, n, bounds, visited)) {
                internal.insert(visited.begin(), visited.end());
            }
            visited.clear();
        }
    }
    solid.insert(internal.begin(), internal.end());
}

int part_a(const std::string &inventory) {
    std::unordered_set<Location, LocationHash> locations;
    parse_inventory(locations, inventory);

    int count = 0;
    for( auto &l : locations) {
        count += count_unoccupied_neighbours(locations, l);
    }

    return count;
}

int part_b(const std::string &inventory) {
    std::unordered_set<Location, LocationHash> locations;
    parse_inventory(locations, inventory);

    fill_in_solid(locations);

    int count = 0;
    for( auto &l : locations) {
        count += count_unoccupied_neighbours(locations, l);
    }

    return count;
}

} // namespace aoc