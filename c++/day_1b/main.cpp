#include <string>
#include <variant>
#include "main.hpp"
#include "day_1b.hpp"

std::variant<int, std::string> day_function(const std::string &input) {
    return aoc::day_1b(input);
}