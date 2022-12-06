#include <string>
#include <variant>
#include "day_3b.hpp"
#include "main.hpp"

std::variant<int, std::string> day_function(const std::string &input) {
    return aoc::day_3b(input);
}