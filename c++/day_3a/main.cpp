#include <string>
#include <variant>
#include "day_3a.hpp"
#include "main.hpp"

std::variant<int, std::string> day_function(const std::string &input) {
    return aoc::day_3a(input);
}