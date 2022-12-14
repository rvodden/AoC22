#include <algorithm>
#include <functional>
#include <optional>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "lib.hpp"

namespace aoc {

using Matrix = std::vector<std::vector<char>>;
using Location = std::pair<int, int>;

void erase_if(std::set<Location>& c, std::function<bool(const Location&)> pred) {
    for (auto it{c.begin()}, end{c.end()}; it != end; ) {
        if (pred(*it)) {
            it = c.erase(it);
        }
        else {
            ++it;
        }
    }
}

std::set<Location> unvisited_neighbours(const int &breadth, const int &depth, const std::set<Location> &unvisited, const Location &loc) {
    int x = loc.first;
    int y = loc.second;
    
    std::set<Location> potential_neighbours = {
        {x+1, y},
        {x-1, y},
        {x, y+1},
        {x, y-1}
    };

    std::function<bool(const Location&)> pred = [breadth, depth](const Location &l) { return l.first < 0 or l.second < 0 or l.first > breadth or l.second > depth; };
    erase_if(potential_neighbours, pred);

    std::set<Location> retval;

    for (auto n : potential_neighbours) {
        auto loc = std::find(unvisited.begin(), unvisited.end(), n);
        if (loc != unvisited.end())
            retval.insert(std::move(n));
    }
    
    return retval;
}

Location unvisited_node_with_lowest_distance(const std::map<Location, int> &distance, const std::set<Location> &unvisited ) {
    int d = std::numeric_limits<int>::max();
    Location min_l;
    for (auto l : unvisited) {
        if (distance.at(l) < d) {
            d = distance.at(l);
            min_l = l;
        }
    }
    if (d == std::numeric_limits<int>::max())
        min_l = *(unvisited.begin());
    return min_l;
}

int part_a(const std::string &inventory) {

    std::stringstream stream(inventory);
    Matrix heights;
    std::string line;

    std::optional<Location> o_start, o_end;

    int y = 0;
    while(std::getline(stream, line)) {
        std::vector<char> row(line.begin(), line.end());

        if ( not o_start.has_value() ) {
            auto loc = std::find(row.begin(), row.end(), 'S');
            if (loc != row.end()) { // Starting location is in this row;
                o_start = {std::distance(row.begin(), loc), y};
            }
        }
        
        if ( not o_end.has_value() ) {
            auto loc = std::find(row.begin(), row.end(), 'E');
            if (loc != row.end()) { // Ending location is in this row;
                o_end = {std::distance(row.begin(), loc), y};
            }
        }

        heights.push_back(row);
        y++;
    }

    Location start = o_start.value();
    Location end = o_end.value();

    // overwrite the start and end pointers so we're in a solvable place
    heights[start.second][start.first] = 'a';
    heights[end.second][end.first] = 'z';

    int depth = heights.size();
    int breadth = heights.front().size();

    std::set<Location> unvisited;
    std::map<Location, int> distance;
    for(int y_ = 0; y_ < depth; y_++) {
        for(int x_ = 0; x_ < breadth; x_++) {
           unvisited.insert({x_, y_});
           distance[{x_, y_}] = std::numeric_limits<int>::max(); 
        }
    }

    Location current = start;
    distance[current] = 0;
    while (unvisited.size() != 0) {
        
        auto neighbours = unvisited_neighbours(breadth, depth, unvisited, current);

        for ( auto l : neighbours ) {
            // potention non-termination when unvisted isn't empty, but no nodes are traversable
            if ( heights[l.second][l.first] - heights[current.second][current.first] > 1 ) continue;
            
            distance[l] = std::min((int)distance[l], distance[current] + 1);
        }

        auto m = std::find(unvisited.begin(), unvisited.end(), current);
        if (m != unvisited.end()) unvisited.erase(m);
        current = unvisited_node_with_lowest_distance(distance, unvisited);

        if (current == end) break;
    }

    return distance[end];
}

int part_b(const std::string &inventory) {
    std::stringstream stream(inventory);
    Matrix heights;
    std::string line;

    std::optional<Location> o_start, o_end;

    int y = 0;
    while(std::getline(stream, line)) {
        std::vector<char> row(line.begin(), line.end());

        if ( not o_start.has_value() ) {
            auto loc = std::find(row.begin(), row.end(), 'E');
            if (loc != row.end()) { // Starting location is in this row;
                o_start = {std::distance(row.begin(), loc), y};
            }
        }
        
        if ( not o_end.has_value() ) {
            auto loc = std::find(row.begin(), row.end(), 'S');
            if (loc != row.end()) { // Ending location is in this row;
                o_end = {std::distance(row.begin(), loc), y};
            }
        }

        heights.push_back(row);
        y++;
    }

    Location start = o_start.value();
    Location end = o_end.value();

    // overwrite the start and end pointers so we're in a solvable place
    char z = 'z';
    char a = 'a';
    heights.at(start.second).at(start.first) = z;
    heights.at(end.second).at(end.first) = a;

    int depth = heights.size();
    int breadth = heights.front().size();

    std::set<Location> unvisited;
    std::map<Location, int> distance;
    for(int y_ = 0; y_ < depth; y_++) {
        for(int x_ = 0; x_ < breadth; x_++) {
           unvisited.insert({x_, y_});
           distance[{x_, y_}] = std::numeric_limits<int>::max(); 
        }
    }

    Location current = start;
    distance[current] = 0;
    while (unvisited.size() != 0) {
        
        auto neighbours = unvisited_neighbours(breadth, depth, unvisited, current);

        if ( distance[current] == std::numeric_limits<int>::max() ) {
            break; // unreachable
        }

        for ( auto l : neighbours ) {
            int height_difference = heights[current.second][current.first] - heights[l.second][l.first];
            if ( height_difference > 1 ) continue;

            distance[l] = std::min((int)distance[l], distance[current] + 1);
        }

        auto m = std::find(unvisited.begin(), unvisited.end(), current);
        if (m != unvisited.end()) unvisited.erase(m);
        current = unvisited_node_with_lowest_distance(distance, unvisited);
    }

    int min_d = std::numeric_limits<int>::max();
    for(int y_ = 0; y_ < depth; y_++) {
        for(int x_ = 0; x_ < breadth; x_++) {
            if (heights[y_][x_] == 'a') {
                min_d = std::min(distance[{x_,y_}], min_d);
            }
        }
    }
    
    return min_d;
}

} // namespace aoc