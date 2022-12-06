#include <iostream>
#include <fstream>
#include <sstream>
#include "main.hpp"


struct VisitTypes {
    void operator() (const int& x) const         { std::cout << x << std::endl; }
    void operator() (const std::string& x) const { std::cout << x << std::endl; }
};

int main(int argc, char** argv) {
    std::ifstream t(argv[1]);
    std::stringstream buffer;
    buffer << t.rdbuf();

    const auto result = day_function(buffer.str());

    std::visit(VisitTypes(), result);

    return 0;
}
