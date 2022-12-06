#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <sstream>

namespace aoc {

// rock = 1
// paper = 2
// scissors = 3

const std::map<const std::string, const int, std::less<>> scores = {
    { "A X" , 0 + 3 },  // rock + lose (play scissors)
    { "A Y" , 3 + 1 },  // rock + draw (play rock)
    { "A Z" , 6 + 2 },  // rock + win (play paper)
    { "B X" , 0 + 1 },  // paper + lose (play rock)
    { "B Y" , 3 + 2 },  // paper + draw (play paper)
    { "B Z" , 6 + 3 },  // paper + win (play scissors)
    { "C X" , 0 + 2 },  // scissors + lose (play paper)
    { "C Y" , 3 + 3 },  // scissors + draw (play scissors)
    { "C Z" , 6 + 1 },  // scissors + win (play rock)
};

int day_2b(const std::string &strategy) {
    std::istringstream ss(strategy);
    std::string line;

    int score = 0;
    int rounds = 0;

    while(std::getline(ss, line)) {
        score += scores.at(line);
        rounds++;
    }

    std::cout << rounds << std::endl;
    return score;
}

}