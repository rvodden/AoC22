#include <iostream>
#include <fstream>
#include <sstream>

#include "main.hpp"

int main(int argc, char** argv) {
    std::ifstream t(argv[1]);
    std::stringstream buffer;
    buffer << t.rdbuf();

    std::cout << day_function(buffer.str()) << std::endl;

    return 0;
}