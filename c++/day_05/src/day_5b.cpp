#include <iostream>
#include <stack>
#include <string>
#include <regex>
#include <vector>

#include "day_5b.hpp"

namespace aoc {

static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}


static std::tuple<std::vector<std::string>, int> read_lines(const std::string &inventory) {

    std::vector<std::string> lines;
    std::stringstream stream(inventory);
    std::string line;

    // whilst we're iterating through everything, find the blank line
    int blank_line_pos = 0;
    bool blank_line_found = false;

    while( std::getline(stream, line) ) {
        lines.push_back(line);
        if (!blank_line_found) {
            if (line == "") {
                blank_line_found = true;
                continue;
            }
            blank_line_pos++;
        }
    }

    return std::make_tuple(lines, blank_line_pos);
}

static std::vector<std::stack<char>> parse_stacks(std::vector<std::string> &lines, const int &blank_line_pos ) {

    // the line before the blank line has the number of stacks in it:
    std::string stack_line = lines[blank_line_pos - 1];
    rtrim(stack_line);
    unsigned long start_of_last_number = stack_line.find_last_of(" ");
    std::string number_of_stacks_string =  stack_line.substr(start_of_last_number);
    const unsigned long number_of_stacks = stoi(number_of_stacks_string);

    // create the requisit number of stacks
    std::vector<std::stack<char>> stacks(number_of_stacks);

    // construct an iterator which starts at the first content line
    auto first_content_line = lines.begin();
    std::advance(first_content_line, blank_line_pos - 2);

    // iterate backwards through the lines until we hit the start
    for(auto content_line = first_content_line; content_line >= lines.begin(); --content_line ) {
        for(unsigned long i = 0; i < number_of_stacks; i++) {
            unsigned long stack_character_position = 4*i + 1;
            if (stack_character_position > (*content_line).length())
                break;
            char content_char = (*content_line)[stack_character_position];
            if (!std::isspace(content_char))
                stacks[i].push((*content_line)[stack_character_position]);
        }
    }

    return stacks;
}

std::string day_5b(const std::string &inventory) {
    
    auto [lines, blank_line_pos] = read_lines(inventory);
    auto stacks = parse_stacks(lines, blank_line_pos);

    auto start = lines.begin();
    std::advance(start, blank_line_pos + 1);

    std::regex regex("move ([0-9]+) from ([0-9]+) to ([0-9]+)");
    std::smatch matches;

    for(auto line = start; line != lines.end(); line++) {
        std::regex_match(*line, matches, regex);
        const int quantity = std::stoi(matches[1]);
        const int source = std::stoi(matches[2]) - 1;
        const int destination = std::stoi(matches[3]) - 1;

        std::string content;

        for(int _i = 0; _i < quantity; _i++) {
            content.insert(0, 1, stacks[source].top());
            stacks[source].pop();
        }
        
        for (char c : content) {
            stacks[destination].push(c);
        }

        content.clear();

    }

    std::string result;

    for(auto stack: stacks) {
        result.push_back(stack.top());
    }

    return result;
}

} // namespace aoc