#include <iostream>
#include <fstream>
#include <sstream>

#include "day_2b.hpp"

int main() {
    std::ifstream t("input.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();

    std::cout << aoc::day_2b(buffer.str()) << std::endl;

    return 0;
}