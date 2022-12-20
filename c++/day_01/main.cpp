#include <iostream>
#include <string>
#include <sstream>
#include <variant>

#include "main.hpp"
#include "lib.hpp"

std::variant<int, std::string> day_function(const std::string &input) {
    std::stringstream s;
    
    s << aoc::part_a(input) << std::endl;
    s << aoc::part_b(input) << std::endl;

    return s.str();
}