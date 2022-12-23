#include <array>
#include <algorithm>
#include <iostream>
#include <limits>
#include <ranges>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <variant>

#include "lib.hpp"

namespace aoc {

bool operator==(const Location &l, const Location &r) {
    return (l.first == r.first) && (l.second == r.second);
}

Location operator+(const Location &l, const Location &r) {
    return { l.first + r.first, l.second + r.second };
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

std::pair<Location, Location> State::get_extents() const {
    int64_t max_x = std::numeric_limits<int64_t>::min();
    int64_t max_y = std::numeric_limits<int64_t>::min();
    int64_t min_x = std::numeric_limits<int64_t>::max();
    int64_t min_y = std::numeric_limits<int64_t>::max();

    for(const auto &[x,y] : _map) {
        max_x = std::max(x, max_x);
        max_y = std::max(y, max_y);
        min_x = std::min(x, min_x);
        min_y = std::min(y, min_y);
    }

    return { {min_x, min_y}, {max_x, max_y} };
}

void State::print_map() const {
    const auto &[min, max] = get_extents();

    for(const auto &y : std::ranges::views::iota(min.second, max.second + 1)) {
        for(const auto &x : std::ranges::views::iota(min.first, max.first + 1)) {
            if(_map.contains({x,y})) {
                std::cout << "#";
                continue;
            }
            std::cout << ".";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

Location State::next_position(const Location &elf) const {
    if (std::ranges::all_of(NEIGHBOURS, [&elf,this](const auto &n){return ! _map.contains(elf + n.second); }))
        return elf;
    
    for ( auto&[criteria, destination] : _rules ) {
        if( std::ranges::all_of(criteria.begin(), criteria.end(),  
            [&elf,this](const Direction &c){ return !_map.contains(elf + NEIGHBOURS.at(c)); } ) 
        ) {
            return elf + NEIGHBOURS.at(destination);
        }
    }
    return elf;
}

bool State::move() {
    std::unordered_map<Location, Location, PairHash> source_destination_map;
    std::unordered_set<Location, PairHash> destinations;
    for (auto& elf : _map) {
        auto destination = next_position(elf);
        if(destinations.contains(destination)) { // another elf is headed here
            source_destination_map[elf] = elf; // don't move
            auto other_elf = std::ranges::find_if(source_destination_map, [&destination](const auto& p) { return p.second == destination; });
            source_destination_map[other_elf->first] = other_elf->first; // tell the other elf not to move either

            // we leave the destination in destinations in case a 3rd elf comes along and wants to move there.
            continue;
        }
        destinations.insert(destination);
        source_destination_map[elf] = destination;
    }
    _map.clear();
    for(const auto &[_, d] : source_destination_map) {
        _map.insert(d);
    }
    return !std::ranges::all_of(source_destination_map, [](const auto &m){ return m.first == m.second; });
}

void State::rotate_rules() {
    Rule rule = _rules.front();
    _rules.erase(_rules.begin());
    _rules.push_back(rule);
}

int64_t State::score() const {
    const auto& [min, max] = get_extents();
    
    int64_t size_of_grid = (1 + max.first - min.first) * (1 + max.second - min.second);
    return size_of_grid - (int64_t)_map.size();
}

void parse_map(Map &map, const std::string &input){
    std::stringstream stream(input);
    std::string line;
    uint64_t y = 0;
    while(std::getline(stream, line)) {
        uint64_t x = 0;
        for (const auto &c : line) {
            switch(c) {
              case ' ':
                break;
              case '.':
                break;
              case '#':
                map.emplace(std::make_pair(x,y));
                break;
              default:
                std::cout << (int) c << std::endl;
                throw std::runtime_error("Invalid character.");
            }
            x++;
        }
        y++;
    }
}

void parse_input(
        Map &map,
        const std::string &input
) {
    parse_map(map, input);
}

int part_a(const std::string &input) {
    Map map;
    parse_input(map, input);

    State state(map);

    for (int i = 0; i < 10; i++) {
        state.move();
        state.rotate_rules();
    }

    return state.score();
}

int part_b(const std::string &input) {
    Map map;
    parse_input(map, input);

    State state(map);

    int64_t i = 1;
    while(state.move()) {
        state.rotate_rules();
        i++;
    }

    return i;
}

} // namespace aoc