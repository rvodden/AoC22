#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "day_3b.hpp"

namespace aoc {

int score (char character) {
    if ( character >= 'a' && character <= 'z' )
        return character - 96;
    else 
        return character - 38;
}

int process_group(std::string elf1, std::string elf2, std::string elf3) {
    
    std::sort(elf1.begin(), elf1.end());
    std::sort(elf2.begin(), elf2.end());
    std::sort(elf3.begin(), elf3.end());

    std::vector<char> e1e2intersection;

    std::set_intersection(
        elf1.begin(), elf1.end(),
        elf2.begin(), elf2.end(),
        std::back_inserter(e1e2intersection)
    );

    std::vector<char> e1e2e3intersection;

    std::set_intersection(
        e1e2intersection.begin(), e1e2intersection.end(),
        elf3.begin(), elf3.end(),
        std::back_inserter(e1e2e3intersection)
    );

    return score(*e1e2e3intersection.begin());
}

int day_3b(const std::string &inventory) {
    std::istringstream stream(inventory);
    std::string elf1;
    std::string elf2;
    std::string elf3;

    int total = 0;

    while (std::getline(stream, elf1) && std::getline(stream, elf2) && std::getline(stream, elf3)) {
        total += process_group(elf1, elf2, elf3);
    }

    return total;
}

} // namespace aoc