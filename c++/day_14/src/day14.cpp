#include <algorithm>
#include <functional>
#include <optional>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <variant>
#include <vector>

#include "day14.hpp"

namespace aoc {

using Location = std::pair<int, int>;

struct LocationHash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};

class Cave {
  public:
    inline void add_rock(const Location &start, const Location &end) {
        if (start.first < end.first) {
            for (int x = start.first; x <= end.first; x++ ) {
                if ( start.second < end.second ) {
                    for(int y = start.second; y <= end.second; y++ ) {
                        rocks.insert({x,y});
                    }
                } else {
                    for(int y = end.second; y <= start.second; y++ ) {
                        rocks.insert({x,y});
                    }
                }
            }
        } else {
            for (int x = end.first; x <= start.first; x++ ) {
                if ( start.second < end.second ) {
                    for(int y = start.second; y <= end.second; y++ ) {
                        rocks.insert({x,y});
                    }
                } else {
                    for(int y = end.second; y <= start.second; y++ ) {
                        rocks.insert({x,y});
                    }
                }
            }
        }
        _height = std::max(start.second, std::max(end.second, _height));
    };
    inline void add_sand(const Location &loc) { sand.insert(loc); };

    bool is_blocked(const Location &l) {
        if (_floor.has_value() ) {
            if ( l.second >= _floor.value() ) return true;
        }

        if (auto s = sand.find(l); s != sand.end()  ) return true;

        auto s = rocks.find(l); 
        return (s != rocks.end());
    }

    int height() { return _height; };

    void set_floor(int f) { _floor = f; };

  
  private:
    std::unordered_set<Location, LocationHash> rocks;
    std::unordered_set<Location, LocationHash> sand;
    int _height = 0;
    std::optional<int> _floor;
};

Location parse_location(std::string::iterator start, std::string::iterator end) {
    Location l;
    
    auto loc = std::find(start, end, ',');
    auto s = std::string(start, loc);
    // std::cout << s << std::endl;
    l.first = std::stoi(s);
    
    s = std::string(loc + 1, end); 
    // std::cout << s << std::endl;
    l.second = std::stoi(s);
    
    return l;
}

Cave parse_data(const std::string &inventory) {
    std::stringstream stream(inventory);
    std::string line;

    Cave cave;
    while (std::getline(stream, line)) {
        auto s = line.begin();
        std::string::iterator e;
        Location a, b;

        e = std::find(s, line.end(), '-');
        a = parse_location(s, e);
        s = e + 3;

        while( s < line.end() ) {
            e = std::find(s, line.end(), '-');
            b = parse_location(s, e);
            cave.add_rock(a, b);
            a = b;
            s = e + 3;
        };
    }

    return cave;
};

int part_a(const std::string &inventory) {
    Cave cave = parse_data(inventory);

    Location sand = {500,0};
    int num = 0;

    auto nexts = [](Location &l) { return std::vector<Location> { 
        { l.first, l.second + 1 }, 
        { l.first - 1, l.second + 1 }, 
        { l.first + 1, l.second + 1} }; 
    };

    while( sand.second < (cave.height() + 1) ) {
        // std::cout << "(" << sand.first << "," << sand.second << ")" << std::endl;
        // std::cout << cave.height() << std::endl;

        for ( auto n : nexts(sand) ) {
            if ( not cave.is_blocked(n) ) {
                sand = n;
                goto cnt; // OMG!
            }
        }

        cave.add_sand(sand);
        sand = {500,0};
        num++;
        cnt:;
    }

    return num;
}

int part_b(const std::string &inventory) {
    Cave cave = parse_data(inventory);

    cave.set_floor(cave.height() + 2);

    Location sand = {500,0};
    int num = 0;

    auto nexts = [](Location &l) { return std::vector<Location> { 
        { l.first, l.second + 1 }, 
        { l.first - 1, l.second + 1 }, 
        { l.first + 1, l.second + 1} }; 
    };

    while( not cave.is_blocked({500,0}) ) {
        // std::cout << "(" << sand.first << "," << sand.second << ")" << std::endl;
        // std::cout << cave.height() << std::endl;

        for ( auto n : nexts(sand) ) {
            if ( not cave.is_blocked(n) ) {
                sand = n;
                goto cnt; // OMG!
            }
        }

        cave.add_sand(sand);
        sand = {500,0};
        num++;
        cnt:;
    }

    return num;
}

} // namespace aoc