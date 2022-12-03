#include <iostream>
#include <map>
#include <functional>
#include <string>
#include <sstream>

namespace aoc {

const std::map<std::string, int, std::less<>> scores = {
    { "A X" , 1 + 3 },  // rock + rock
    { "A Y" , 2 + 6 },  // rock + paper
    { "A Z" , 3 + 0 },  // rock + scissors
    { "B X" , 1 + 0 },  // paper + rock
    { "B Y" , 2 + 3 },  // paper + paper
    { "B Z" , 3 + 6 },  // paper + scissors
    { "C X" , 1 + 6 },  // scissors + rock
    { "C Y" , 2 + 0 },  // scissors + paper
    { "C Z" , 3 + 3 },  // scissors + scissors
};

int day_2a(const std::string &strategy) {
    std::istringstream ss(strategy);
    std::string line;

    int score = 0;

    while(std::getline(ss, line)) {
        score += scores.at(line);
    }

    return score;
}

}