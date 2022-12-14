#include <iostream>
#include <fstream>
#include <sstream>
#include <variant>

#include "day14.hpp"
#include "main.hpp"


std::variant<int, std::string> day_function(const std::string &inventory) {
    std::stringstream s;
    
    s << aoc::part_a(inventory) << std::endl;
    s << aoc::part_b(inventory) << std::endl;

    return s.str();
}