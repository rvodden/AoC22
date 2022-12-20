#include <iostream>
#include <fstream>
#include <sstream>
#include <variant>

#include "day_6a.hpp"
#include "day_6b.hpp"
#include "main.hpp"


std::variant<int, std::string> day_function(const std::string &inventory) {
    std::stringstream s;

    s << aoc::day_6a(inventory) << std::endl;
    s << aoc::day_6b(inventory) << std::endl;

    return s.str();
}