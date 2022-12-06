#include <iostream>
#include <fstream>
#include <sstream>
#include <variant>

#include "day_6a.hpp"
#include "main.hpp"


std::variant<int, std::string> day_function(const std::string &inventory) {
    return aoc::day_6a(inventory);
}