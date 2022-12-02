
#include <iostream>
#include <fstream>
#include <sstream>

#include "day_1b.hpp"

int main() {
    std::ifstream t("input.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();

    aoc::CalorieCounter calorie_counter;

    std::cout << calorie_counter.day_1(buffer.str()) << std::endl;

    return 0;
}