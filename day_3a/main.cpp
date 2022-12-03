#include <iostream>
#include <fstream>
#include <sstream>

#include "day_3a.hpp"

int main() {
    std::ifstream t("input.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();

    std::cout << aoc::day_3a(buffer.str()) << std::endl;

    return 0;
}