#include <algorithm>
#include <functional>
#include <optional>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

#include "day14.hpp"

namespace aoc {

using Location = std::pair<int, int>;

class Cave {
  public:
    inline void add_rock(const Location &start, const Location &end) {
        if ( start.second > end.second or start.first > end.first ) 
            rocks.push_back({end, start});
        else
            rocks.push_back({start, end});
        _height = std::max(start.second, std::max(end.second, _height));
    };
    inline void add_sand(const Location &loc) { sand.push_back(loc); };

    void print_rocks() {
        for (auto line : rocks) {
            std::cout << "[(" << line.first.first << "," << line.first.second << "),(";
            std::cout << line.second.first << "," << line.second.second << ")]" << std::endl;
        };
    }

    bool is_rock(const Location &l) {
        for (auto line : rocks) {
            if ( line.first.first == line.second.first ) { // vertical line
                if ( l.first != line.first.first )
                    continue;

                if(line.first.second <= l.second and line.second.second >= l.second)
                    return true;
            }
            
            if ( l.second != line.first.second )
                continue;

            if (line.first.first <= l.first and line.second.first >= l.first)
                return true;
        }
        return false;
    }

    bool is_blocked(const Location &l) {
        if (_floor.has_value() ) {
            if ( l.second >= _floor.value() ) return true;
        }

        for ( auto s : sand ) {
            if (l == s) return true;
        }
        return is_rock(l);
    }

    int height() { return _height; };

    void set_floor(int f) { _floor = f; };

  private:
    std::vector<std::pair<Location, Location>> rocks;
    std::vector<Location> sand;
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

    // std::cout << cave.height() << std::endl;

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

    // std::cout << cave.height() << std::endl;

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