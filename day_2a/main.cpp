#include <iostream>
#include <fstream>
#include <sstream>

#include "day_2a.hpp"

int main() {
    std::ifstream t("input.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();

    std::cout << aoc::day_2a(buffer.str()) << std::endl;

    return 0;
}