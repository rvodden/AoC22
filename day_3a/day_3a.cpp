#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "day_3a.hpp"

namespace aoc {

int score (char character) {
    if ( character >= 'a' && character <= 'z' )
        return character - 96;
    else 
        return character - 38;
}

int process_line(const std::string_view &inventory) {
    
    // find position of middle of string
    unsigned long middle = inventory.length() / 2;  // question guarantees even input

    std::string_view first_compartment = inventory.substr(0, middle);
    std::string_view second_compartment = inventory.substr(middle);

    std::cout << first_compartment << std::endl;
    std::cout << second_compartment << std::endl;

    for ( char character : first_compartment ) {
        auto loc = second_compartment.find(character);
        if (loc != std::string::npos)
            return score(character);
    }

    return 0; // this should never happen
}

int day_3a(const std::string &inventory) {
    std::istringstream stream(inventory);
    std::string line;

    int total = 0;

    while (std::getline(stream, line)) {
        total += process_line(line);
    }

    return total;
}

} // namespace aoc