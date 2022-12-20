#include "lib.hpp"

#include <algorithm>
#include <numeric>
#include <sstream>
#include <vector>

namespace aoc {

const static std::string delimiter = "\n\n";

int part_a(std::string report) {
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

int part_b (std::string report) {
    size_t pos = 0;
    std::string calorie_list;
    std::stringstream stream;
    std::string calorie;

    std::vector<int> calorie_vector;

    int calories = 0;

    do {
        pos = report.find(delimiter);
        calorie_list = report.substr(0, pos);
        stream = std::stringstream(calorie_list);

        while(std::getline(stream, calorie)) {
            calories += stoi(calorie);
        }
     
        calorie_vector.push_back(calories);
        calories = 0;
        report.erase(0, pos + delimiter.length());
    } while (pos != std::string::npos);
    
    std::sort(calorie_vector.rbegin(), calorie_vector.rend());

    return std::reduce(calorie_vector.begin(), calorie_vector.begin() + 3);
}

}
