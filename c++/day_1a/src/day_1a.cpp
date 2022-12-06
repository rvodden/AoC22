#include "day_1a.hpp"

#include <sstream>
#include <vector>

namespace aoc {

const static std::string delimiter = "\n\n";

int day_1a(std::string report) {
    size_t pos = 0;
    std::string calorie_list;
    std::stringstream stream;
    std::string calorie;

    int calories = 0;
    int max_calories = 0;

    while((pos = report.find(delimiter)) != std::string::npos) {
        calorie_list = report.substr(0, pos);
        stream = std::stringstream(calorie_list);

        while(std::getline(stream, calorie)) {
            calories += stoi(calorie);
        }
     
        if (calories > max_calories) max_calories = calories;
        calories = 0;
        report.erase(0, pos + delimiter.length());
    }

    return max_calories;
}

}
