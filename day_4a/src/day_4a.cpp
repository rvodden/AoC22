#include <string>
#include <regex>

#include "day_4a.hpp"

namespace aoc {

int day_4a(const std::string &inventory) {

    std::stringstream stream(inventory);
    std::string line;

    std::regex regex("([0-9]+)");
    std::vector<int> sections;

    int result = 0;

    while(std::getline(stream, line)) {

        auto begin = std::sregex_iterator(line.begin(), line.end(), regex);
        auto end = std::sregex_iterator();

        for (auto match = begin; match != end; ++match) {
            const std::string &section_string = (*match).str();
            sections.push_back(std::stoi(section_string));
        }

        if( 
            ( sections[0] <= sections[2] && sections[1] >= sections[3] ) || // first contains the second
            ( sections[2] <= sections[0] && sections[3] >= sections[1] ) // second contains the first
        ) result++;

        sections.clear();
    }

    return result;
}

} // namespace aoc