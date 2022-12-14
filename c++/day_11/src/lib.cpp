#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "lib.hpp"

namespace aoc {

class Monkey {
  public:
    std::vector<int> items;
    std::function<int(const int&)> opp;
    std::function<bool(const int&)> test;

    int monkey_if_true;
    int monkey_if_false;
};

std::stringstream& getlines(std::stringstream &stream, std::vector<std::string> &lines, const int &number_of_lines) {
    lines.clear();
    int n = number_of_lines;
    while (n--) {
        std::string line;
        std::getline(stream, line);
        lines.push_back(std::move(line));

    }
    return stream;
}

Monkey parse_monkey(std::vector<std::string> lines) {
    Monkey monkey;
    lines[0].pop_back(); //nuke the colon

    // read monkey number
    int monkey_number = std::stoi(lines[0].substr(7));

    // read items
    std::stringstream itemsstream(lines[1].substr(18));
    std::string item;
    while (std::getline(itemsstream, item, ',')) {
        monkey.items.push_back(stoi(item));
    }

    // read operation
    char operation = lines[2][23];
    std::string operand = lines[2].substr(25);

    if (operand == "old") {
        if (operation == '*')
            monkey.opp = [](const int &x) { return x * x; };
        else
            monkey.opp = [](const int &x) { return x + x; };
    } else {
        int i = std::stoi(operand);
        if (operation == '*')
            monkey.opp = [i](const int &x) { return x * i; };
        else
            monkey.opp = [i](const int &x) { return x + i; };
    }

    // read test
    int divisor = std::stoi(lines[3].substr(21));
    monkey.test = [divisor](int x){ return x % divisor; };

    // read destinations;
    monkey.monkey_if_true = std::stoi(lines[4].substr(29));
    monkey.monkey_if_false = std::stoi(lines[5].substr(29));

    return monkey;
}

int part_a(const std::string &inventory) {
    std::stringstream stream(inventory);
    std::vector<std::string> lines;
    std::vector<Monkey> monkeys;
    Monkey monkey;
    while (getlines(stream, lines, 7)) {
        monkey = parse_monkey(lines);
        monkeys.push_back(monkey);
    }
    getlines(stream, lines, 7);
    monkey = parse_monkey(lines);
    monkeys.push_back(monkey);

    for(auto m : monkeys) {
        std::cout << m.items[0] << std::endl;
    }
    return 0;
}

std::string part_b(const std::string &inventory) {
    return "";
}

} // namespace aoc