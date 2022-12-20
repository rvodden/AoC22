#include <string>
#include <variant>
#include "day_4a.hpp"
#include "day_4b.hpp"
#include "main.hpp"

std::variant<int, std::string> day_function(const std::string &input) {
    std::stringstream s;
    s << aoc::day_4a(input) << std::endl;
    s << aoc::day_4b(input) << std::endl;
    return s.str();
}