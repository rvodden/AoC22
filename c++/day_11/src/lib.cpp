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

std::stringstream& getlines(std::stringstream &stream, std::vector<std::string> &lines, const int64_t &number_of_lines) {
    lines.clear();
    int64_t n = number_of_lines;
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
    int64_t monkey_number = std::stoi(lines[0].substr(7));

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
            monkey.opp = [](const int64_t &x) { return x * x; };
        else
            monkey.opp = [](const int64_t &x) { return x + x; };
    } else {
        int64_t i = std::stoi(operand);
        if (operation == '*')
            monkey.opp = [i](const int64_t &x) { return x * i; };
        else
            monkey.opp = [i](const int64_t &x) { return x + i; };
    }

    // read test
    int64_t divisor = std::stoi(lines[3].substr(21));
    monkey.divisor = divisor; 
    monkey.test = [divisor](int64_t x){ return (x % divisor) == 0; };

    // read destinations;
    monkey.monkey_if_true = std::stoi(lines[4].substr(29));
    monkey.monkey_if_false = std::stoi(lines[5].substr(29));

    return monkey;
}

int64_t part_a(const std::string &inventory) {
    std::stringstream stream(inventory);
    std::vector<std::string> lines;
    std::vector<Monkey> monkeys;
    
    Monkey monkey;
    
    while (getlines(stream, lines, 7)) {
        monkey = parse_monkey(lines);
        monkeys.push_back(monkey);
    }

    for (int64_t i = 0; i < 20; i++) {
        for(Monkey &monkey : monkeys) {
            for( auto item = monkey.items.begin(); item < monkey.items.end(); item++ ) {
                *item = monkey.opp(*item);
                *item /= 3;
                if ( monkey.test(*item) ) {
                    monkeys[monkey.monkey_if_true].items.emplace_back(*item);
                } else {
                    monkeys[monkey.monkey_if_false].items.emplace_back(*item);
                }
                monkey.count++;
            } 
            monkey.items.clear();
        }
    }

    std::vector<int64_t> counts;
    for(Monkey monkey : monkeys) {
        counts.push_back(monkey.count);
    }
    std::sort(counts.rbegin(), counts.rend());

    return counts[0] * counts[1];
}

int64_t part_b(const std::string &inventory) {
    std::stringstream stream(inventory);
    std::vector<std::string> lines;
    std::vector<Monkey> monkeys;
    
    Monkey monkey;
    
    while (getlines(stream, lines, 7)) {
        monkey = parse_monkey(lines);
        monkeys.push_back(monkey);
    }    
    
    int64_t modulus = 1;
    for (const auto &mk: monkeys) {
        modulus = std::lcm(modulus, mk.divisor);
    }

    for (int64_t i = 0; i < 10000; i++) {
        for(Monkey &monkey : monkeys) {
            for( auto item = monkey.items.begin(); item < monkey.items.end(); item++ ) {
                *item = monkey.opp(*item);
                *item %= modulus;
                if ( monkey.test(*item) ) {
                    monkeys[monkey.monkey_if_true].items.emplace_back(*item);
                } else {
                    monkeys[monkey.monkey_if_false].items.emplace_back(*item);
                }
                monkey.count++;
            } 
            monkey.items.clear();
        }
    }

    std::vector<int64_t> counts;
    for(Monkey monkey : monkeys) {
        counts.push_back(monkey.count);
    }
    std::sort(counts.rbegin(), counts.rend());

    return counts[0] * counts[1];
}

} // namespace aoc