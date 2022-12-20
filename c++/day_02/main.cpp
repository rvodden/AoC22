#include <string>
#include <sstream>
#include <variant>

#include "day_2a.hpp"
#include "day_2b.hpp"
#include "main.hpp"

std::variant<int, std::string> day_function(const std::string &input) {
    std::stringstream s;

    s << aoc::day_2a(input) << std::endl;
    s << aoc::day_2b(input) << std::endl;

    return s.str();
}