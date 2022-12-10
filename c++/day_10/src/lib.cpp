#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "lib.hpp"

namespace aoc {

std::vector<int> parse(std::string inventory) {
    std::stringstream stream(inventory);
    std::string line;

    std::vector<int> xs = {1};
    int d;
    while(std::getline(stream, line)) {
        if (line == "noop") {
            xs.push_back(0);
            continue;
        }
        
        d = std::stoi(line.substr(5));
        xs.push_back(0); xs.push_back(d);
    }

    std::partial_sum(xs.begin(), xs.end(), xs.begin());
    return xs;
}

int part_a(const std::string &inventory) {
    auto xs = parse(inventory);
    int total = 0;
    int cycle = 20;
    for (auto s = xs.begin() + 19; s < xs.end(); s += 40) {
        total += *s * cycle;
        cycle += 40;
    }

    return total;
}

std::string part_b(const std::string &inventory) {
    std::stringstream s;
    auto xs = parse(inventory);
    xs.pop_back(); // don't know why, but I get an extra dot without this!
    int idx = 0;
    for(auto x = xs.begin(); x < xs.end(); x++) {
        s << (std::abs(idx - *x) <= 1 ? "#" : ".");
        if (idx == 39) {
            s << std::endl;
            idx = 0;
            continue;
        }
        idx++;
    }
    return s.str();
}

} // namespace aoc