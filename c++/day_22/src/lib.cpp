#include <stdexcept>
#include <iostream>
#include <sstream>
#include <string>
#include <variant>
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
            s << "▶";
            break;
        case Orientation::DOWN:
            s << "▼";
            break;
        case Orientation::LEFT:
            s << "◀";
            break;
        case Orientation::UP:
            s << "▲";
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
    s << "(" << l.first << "," << l.second << ")";
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
    if(_map.at(nl)) _location = nl; // check we're not headed into a wall;
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

void generate_edge_mappings(const Net &net, const NetScaling &net_scaling, WrapAround &wrap_around) {
    for(auto &[source, destination] : net) {
        auto &[source_face, source_edge, source_bearing] = source;
        auto &[destination_face, destination_edge, destination_bearing] = destination;

        int64_t source_begin_x, source_end_x, source_begin_y, source_end_y;     
        if(source_bearing == Bearing::ASCENDING) {
            source_begin_x = net_scaling[source_face].first.first;
            source_end_x = net_scaling[source_face].second.first;
            source_begin_y = net_scaling[source_face].first.second;
            source_end_y = net_scaling[source_face].second.second;
        } else {
            source_begin_x = net_scaling[source_face].second.first;
            source_end_x = net_scaling[source_face].first.first;
            source_begin_y = net_scaling[source_face].second.second;
            source_end_y = net_scaling[source_face].first.second;
        }
        
        int64_t destination_begin_x, destination_end_x, destination_begin_y, destination_end_y;     
        if(destination_bearing == Bearing::ASCENDING) {
            destination_begin_x = net_scaling[destination_face].first.first;
            destination_end_x = net_scaling[destination_face].second.first;
            destination_begin_y = net_scaling[destination_face].first.second;
            destination_end_y = net_scaling[destination_face].second.second;
        } else {
            destination_begin_x = net_scaling[destination_face].second.first;
            destination_end_x = net_scaling[destination_face].first.first;
            destination_begin_y = net_scaling[destination_face].second.second;
            destination_end_y = net_scaling[destination_face].first.second;
        }
    }
}

int part_b(const std::string &input) {
    return 0;
}

} // namespace aoc