#include <string>
#include <variant>
#include "day_4b.hpp"
#include "main.hpp"

std::variant<int, std::string> day_function(const std::string &input) {
    return aoc::day_4b(input);
}