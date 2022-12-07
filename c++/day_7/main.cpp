#include <iostream>
#include <fstream>
#include <sstream>
#include <variant>

#include "day_7.hpp"
#include "main.hpp"


std::variant<int, std::string> day_function(const std::string &inventory) {
    std::stringstream s;
    
    s << aoc::day_7a(inventory) << std::endl;
    s << aoc::day_7b(inventory) << std::endl;

    return s.str();
}