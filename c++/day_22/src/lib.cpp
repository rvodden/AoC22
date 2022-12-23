#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <variant>
#include <ranges>
#include <regex>

#include "lib.hpp"

namespace aoc {

Orientation& operator--(Orientation &o) {
    o = (Orientation)(((int)o - 1 )% 4);
    if( (int)o < 0 ) o = (Orientation)((int)o + 4);
    return o;
}

Orientation& operator++(Orientation &o) {
    o = (Orientation)(((int)o + 1) % 4);
    if( (int)o < 0 ) o = (Orientation)((int)o + 4);
    return o;
}

std::ostream& operator<<(std::ostream& s, const Orientation &l) {
    switch(l) {
        case Orientation::RIGHT:
            // s << "▶";
            s << "Right";
            break;
        case Orientation::DOWN:
            // s << "▼";
            s << "Down";
            break;
        case Orientation::LEFT:
            // s << "◀";
            s << "Left";
            break;
        case Orientation::UP:
            // s << "▲";
            s << "Up";
            break;
        default:
            std::cout << (int)l << std::endl;
            throw std::runtime_error("Invalid Orientation.");
    }
    return s;
}

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
    s << "(" << l.first << ", " << l.second << ")";
    return s;
}

std::ostream& operator<<(std::ostream& s, const Direction &d) {
    switch(d) {
        case Direction::LEFT:
            s << "L";
            break;
        case Direction::RIGHT:
            s << "R";
            break;
    }
    return s;
}

Location State::find_start_location() const {
    int64_t y = 0;
    int64_t x = std::numeric_limits<int16_t>::max();
    auto loc = std::ranges::find_if(
            _map.cbegin(), 
            _map.cend(), 
            [&](const auto &l) { return (l.first.second == y); });
    while(loc != _map.cend() ) {
        x = std::min(loc->first.first, x);
        auto new_loc = std::ranges::find_if(
                std::next(loc),
                _map.cend(), 
                [&](const auto &l) { return (l.first.second == y); });
        loc = new_loc;
    }

    return {x, y};
}

Location _wrap_around(const Map &map, const Location &location, const Location &delta) {
    if(!map.contains(location + delta) ) return location;
    return _wrap_around(map, location + delta, delta);
}

void State::wrap_around( const Location &delta ) {
    Location nl = _wrap_around(_map, _location, delta * -1);
    if(_map.at(nl)) { // check we're not headed into a wall;
        _location = nl;
    }
}

void PartTwoState::wrap_around( const Location &delta ) {
    auto nl = _wrap_around.at({_location, _orientation});
    if(_map.at(nl.first)) {
        _location = nl.first;
        _orientation = nl.second;
    };
}

std::ostream& operator<<(std::ostream& s, const Edge &e) {
    switch(e) {
        case Edge::EAST:
            s << "EAST";
            break;
        case Edge::SOUTH:
            s << "SOUTH";
            break;
        case Edge::NORTH:
            s << "NORTH";
            break;
        case Edge::WEST:
            s << "WEST";
            break;
    }
    return s;
}

int64_t State::password() const {
    return (_location.second + 1) * 1000 + (_location.first + 1) * 4 + (int64_t)(_orientation); 
}

void State::move(int64_t distance) {
    if (distance-- == 0) return;
    Location delta;
    switch(_orientation) {
        case Orientation::RIGHT:
            delta = {1, 0};
            break;
        case Orientation::DOWN:
            delta = {0, 1};
            break;
        case Orientation::LEFT:
            delta = {-1, 0};
            break;
        case Orientation::UP:
            delta = {0, -1};
            break;
    }

    if(!_map.contains(_location + delta)) {
        wrap_around(delta);
        move(distance);
        return;
    }

    if(!_map.at(_location + delta)) {
        // hit a wall
        return;
    }

    _location += delta;
    move(distance);
}

void State::turn(const Direction &d) {
    switch(d) {
      case Direction::LEFT:
        --_orientation;
        break;
      case Direction::RIGHT:
        ++_orientation;
        break;
    }
}

void State::print_map() const {
    int64_t max_x = 0;
    int64_t max_y = 0;

    for(const auto &[l,_] : _map) {
        auto &[x,y] = l;
        max_x = std::max(x, max_x);
        max_y = std::max(y, max_y);
    }

    for(const int &y : std::ranges::views::iota(0, max_y+1)) {
        for(const int &x : std::ranges::views::iota(0, max_x + 1)) {
            if(_location == std::make_pair(x,y)) {
                std::cout << _orientation;
                continue;
            }
            if(!_map.contains({x,y})) {
                std::cout << " ";
                continue;
            }
            if(!_map.at({x,y})) {
                std::cout << "#";
                continue;
            }
            std::cout << ".";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
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
                map.try_emplace(std::make_pair(x,y), true);
                break;
              case '#':
                map.try_emplace(std::make_pair(x,y), false);
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

void parse_route(Route &route, const std::string &input) {
    std::regex regex("(\\d+|[LR]{1})");
    std::smatch match;
    auto begin = std::sregex_iterator(input.begin(), input.end(), regex);
    auto end = std::sregex_iterator();
    for(auto i = begin; i != end; i++) {
        match = *i;
        int64_t distance;
        try{
            distance = std::stoi(match[1].str());
            route.push(distance);
        } catch( std::invalid_argument &e) {
            route.push(static_cast<Direction>(match[1].str().front()));
        };
    }
}

void parse_input(
        Map &map,
        Route &route,
        const std::string &input
) {
    std::array<std::string,2> input_blocks;
    
    const std::string delimiter = "\n\n";
    const auto delimiter_location = input.find(delimiter);
    input_blocks[0] = input.substr(0, delimiter_location);
    input_blocks[1] = input.substr(delimiter_location + delimiter.length());

    parse_map(map, input_blocks[0]);
    parse_route(route, input_blocks[1]);
}

int part_a(const std::string &input) {
    Map map;
    Route route;
    parse_input(map, route, input);

    State state(map);

    while( !route.empty() ) {
        Step step = route.front();
        route.pop();
        if(std::holds_alternative<int64_t>(step)) {
            state.move(std::get<int64_t>(step));
        } else {
            state.turn(std::get<Direction>(step));
        }
    };

    int64_t password = state.password();
    std::cout << password << std::endl;

    return password;
}

Orientation new_orientation(const Edge &destination) {
    using enum Edge;
    using enum Orientation;
    switch(destination) {
        case NORTH:
            return DOWN;
        case WEST:
            return RIGHT;
        case SOUTH:
            return UP;
        case EAST:
            return LEFT;
    }
    __builtin_unreachable();
}

Orientation old_orientation(const Edge &destination) {
    using enum Edge;
    using enum Orientation;
    switch(destination) {
        case NORTH:
            return UP;
        case WEST:
            return LEFT;
        case SOUTH:
            return DOWN;
        case EAST:
            return RIGHT;
    }
    __builtin_unreachable();
}
/**
 * Returns the minimum and maximum x and y co-ordinates of an edge, given the two corners of a face.
 * 
 * { {min_x, max_x}, {min_y, max_y}}
*/
Range edge_range(const Range &extent, const Edge &edge, const Bearing &bearing) {
    using enum aoc::Edge;
    using enum aoc::Bearing;
    switch(edge) {
        case NORTH:
            if(bearing == ASCENDING)
                return {{ extent.first.first, extent.second.first }, {extent.first.second, extent.first.second}};
            return {{ extent.second.first, extent.first.first }, {extent.first.second, extent.first.second}};
        case EAST:
            if(bearing == ASCENDING)
                return {{ extent.second.first, extent.second.first }, {extent.first.second, extent.second.second}};
            return {{ extent.second.first, extent.second.first}, {extent.second.second, extent.first.second}};
        case SOUTH:
            if(bearing == ASCENDING)
                return {{ extent.first.first, extent.second.first }, {extent.second.second, extent.second.second}};
            return {{ extent.second.first, extent.first.first }, {extent.second.second, extent.second.second}};
        case WEST:
            if(bearing == ASCENDING)
                return {{ extent.first.first, extent.first.first}, {extent.first.second, extent.second.second}};
            return {{ extent.first.first, extent.first.first}, {extent.second.second, extent.first.second}};
    }
    __builtin_unreachable(); // nuke the compiler warning (yuck)
}

void generate_edge_mappings(const Net &net, const NetScaling &net_scaling, WrapAround &wrap_around) {
    for(auto &[source, destination] : net) {
        auto &[source_face, source_edge, source_bearing] = source;
        auto &[destination_face, destination_edge, destination_bearing] = destination;

        int64_t source_begin_x, source_end_x, source_begin_y, source_end_y;     
        const auto &[xrange, yrange] = edge_range(net_scaling.at(source_face), source_edge, source_bearing);
        source_begin_x = xrange.first;
        source_end_x = xrange.second;
        source_begin_y = yrange.first;
        source_end_y = yrange.second;

        int64_t destination_begin_x, destination_end_x, destination_begin_y, destination_end_y;     
        const auto &[x_range, y_range] = edge_range(net_scaling.at(destination_face), destination_edge, destination_bearing);
        destination_begin_x = x_range.first;
        destination_end_x = x_range.second;
        destination_begin_y = y_range.first;
        destination_end_y = y_range.second;

        std::cout << "Map face " << +source_face << " edge " << source_edge << " to face " << +destination_face << " edge " << destination_edge << std::endl;
        std::cout << source_begin_x << " - " << source_end_x << " to " << destination_begin_x << " - " << destination_end_x << std::endl;
        std::cout << source_begin_y << " - " << source_end_y << " to " << destination_begin_y << " - " << destination_end_y << std::endl;
        std::cout << std::endl;

        const auto& delta = [](const int64_t &begin, const int64_t &end) { 
            if (end > begin) return 1;
            if (end == begin) return 0;
            return -1;
        };

        auto source_delta_x = delta(source_begin_x, source_end_x);
        auto source_delta_y = delta(source_begin_y, source_end_y);
        auto destination_delta_x = delta(destination_begin_x, destination_end_x);
        auto destination_delta_y = delta(destination_begin_y, destination_end_y);

        auto sx = source_begin_x;
        auto dx = destination_begin_x;
        auto sy = source_begin_y;
        auto dy = destination_begin_y;

        const auto& abs = [](int i){return std::abs(i);};

        const auto &abs_values = std::vector {source_begin_x - source_end_x,
            source_begin_y - source_end_y,
            destination_begin_x - destination_end_x,
            destination_begin_y - destination_end_y} | std::views::transform(abs);
        
        // for(const auto &i : abs_values) {
        //     std::cout << i << std::endl;
        // }

        const auto &loops = std::ranges::max(abs_values);

        // std::cout << "loops: " << loops << std::endl;
        for( int i = 0; i <= loops; i++ ) {
            std::cout << "(" << sx << "," << sy << ") <-> (" << dx << "," << dy << ")" << std::endl;
            wrap_around[{{sx, sy}, old_orientation(source_edge)}] = {{dx, dy}, new_orientation(destination_edge)};
            wrap_around[{{dx, dy}, old_orientation(destination_edge)}] = {{sx, sy}, new_orientation(source_edge)};
            sx += source_delta_x;
            sy += source_delta_y;
            dx += destination_delta_x;
            dy += destination_delta_y;
        }
    }
}

int64_t calculate_cube_journey(const std::string &input, const Net &net, const NetScaling &net_scaling) {
    WrapAround wrap_around;
    generate_edge_mappings(net, net_scaling, wrap_around);

    Map map;
    Route route;
    parse_input(map, route, input);

    PartTwoState state(map, wrap_around);

    while( !route.empty() ) {
        Step step = route.front();
        route.pop();
        if(std::holds_alternative<int64_t>(step)) {
            state.move(std::get<int64_t>(step));
            std::cout << state.get_position().first << " " << state.get_position().second << " " << std::get<int64_t>(step) << std::endl;
        } else {
            state.turn(std::get<Direction>(step));
            std::cout << std::get<Direction>(step) << std::endl;
        }
    };

    int64_t password = state.password();
    std::cout << password << std::endl;

    return password;
}

int64_t part_b(const std::string &input) {
    return calculate_cube_journey(input, INPUT_NET, INPUT_NET_SCALING);
}

} // namespace aoc