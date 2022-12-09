#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "lib.hpp"

namespace aoc {

using location = std::pair<int,int>; 

const std::map<char, location> DIR = {
    {'R' ,{1,0} },
    {'L' ,{-1,0} },
    {'U' ,{0,1} },
    {'D' ,{0,-1} }
};

location operator+(const location & left, const location & right) {   
    return {left.first + right.first, left.second + right.second};                                    
}

location operator-(const location & left, const location & right) {   
    return {left.first - right.first, left.second - right.second};                                    
}

int normalise(const int &i) {
    return i == 0 ? 0 : i / std::abs(i);
}

location normalise(const location &loc) {
    return { normalise(loc.first) , normalise(loc.second) };
}

bool adjacent(const location &loc) {
    return std::max(std::abs(loc.first), std::abs(loc.second)) <= 1;
}

int part_a(const std::string &inventory) {
    std::stringstream stream(inventory);
    std::string line;

    std::set<location> locations_tail_has_visited;
    
    location head = {0,0};
    location tail = {0,0};

    locations_tail_has_visited.insert(tail);

    while(std::getline(stream, line)) {
        const location direction = DIR.at(line[0]);
        const int quantity = stoi(line.substr(2));

        for (int i = 0; i < quantity; i++) {
            head = head + direction; // consider overriding +=
            location delta = tail - head;

            if(!adjacent(delta))
                tail = tail - normalise(delta);
            locations_tail_has_visited.insert(tail);
        }

    }

    return locations_tail_has_visited.size();
}


int part_b(const std::string &inventory) {
    std::stringstream stream(inventory);
    std::string line;

    std::set<location> locations_tail_has_visited;

    std::vector<location> rope(10, {0,0});

    locations_tail_has_visited.insert(rope.back());

    while(std::getline(stream, line)) {
        const location direction = DIR.at(line[0]);
        const int quantity = stoi(line.substr(2));

        for (int i = 0; i < quantity; i++) {
            rope[0] = rope[0] + direction;
            
            auto s = rope.begin();
            auto t = rope.begin() + 1;
            while (t != rope.end()) {

                location delta = *t - *s;

                if(!adjacent(delta))
                    *t = *t - normalise(delta);
                s++; t++;
            }
            
            locations_tail_has_visited.insert(rope.back());
        }

    }

    return locations_tail_has_visited.size();
}

} // namespace aoc