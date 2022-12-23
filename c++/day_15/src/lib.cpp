#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <optional>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "lib.hpp"

namespace aoc {

using Location = std::pair<int,int>;

void parse_inventory(std::vector<std::pair<Location, Location>> &readings, const std::string &inventory) {
    std::regex regex(R"R(Sensor at x=(-?\d+), y=(-?\d+): closest beacon is at x=(-?\d+), y=(-?\d+))R");
    std::stringstream stream(inventory);
    std::string line;
    std::smatch matches;
    while (std::getline(stream, line)) {
        if (std::regex_search(line, matches, regex)) {
            readings.push_back({
                {std::stoi(matches[1]), std::stoi(matches[2])}, 
                {std::stoi(matches[3]), std::stoi(matches[4])}
            });
        }
    }
}

std::optional<std::pair<int, int>> impact_on_row(
    const Location &sensor_location, 
    const int& distance_to_nearest_beacon, 
    const int& row_of_interest)
{
    int delta = distance_to_nearest_beacon - std::abs(sensor_location.second - row_of_interest);
    // if the row of interest is too far away, this sensor will have no impact on it
    if ( delta < 0 )
        return std::nullopt;   

    return std::make_pair(
        sensor_location.first - delta,
        sensor_location.first + delta
    );
}

int taxicab_distance(const Location& a, const Location& b) {
    return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

void get_covered_ranges_and_beacons_on_row(
    const std::vector<std::pair<Location, Location>> &readings,
    const int &row,
    std::vector<std::pair<int, int>> &ranges,
    std::set<Location> &beacons

) {
    // for each sensor and beacon work out 
    // what range can be excluded from the row
    // in question
    std::vector<std::pair<int, int>> temp_ranges;
    for( const auto &[sensor, beacon] : readings ) {
        auto d = taxicab_distance(sensor, beacon);
        auto range = impact_on_row(sensor, d, row);

        if (range.has_value()) 
            temp_ranges.push_back(range.value());

        if (beacon.second == row)
            beacons.insert(beacon);
    }

    // sort each of those ranges
    std::sort(temp_ranges.begin(), temp_ranges.end(), [](auto l, auto r){ return l.first < r.first; } );
    
    // now consolidate overlapping ranges
    auto r = temp_ranges.begin();
    int high = r->second; 
    int low = r->first;
    r++;
    while (r < temp_ranges.end()) {
        if (std::max(low, r->first) <= std::min(high, r->second))
            high = std::max(r->second, high);
        else {
            ranges.push_back({low, high});
            low = r->first;
            high = r->second;
        }
        r++;
    }
    ranges.push_back({low, high});

}

int count_beacon_slots(const std::vector<std::pair<Location, Location>> &readings, const int &row) {
    std::vector<std::pair<int, int>> ranges;
    std::set<Location> beacons;

    get_covered_ranges_and_beacons_on_row(readings, row, ranges, beacons);

    int count = 0;
    for(auto &[x,y]: ranges) {
        count += y - x + 1;
        for(auto &[bx, _] : beacons) {
            if (x <= bx and bx <= y )
                count--;
        }
    }

    return count;
}

int count_beacon_slots(const std::string &inventory, const int &row) {
    std::vector<std::pair<Location, Location>> readings;
    parse_inventory(readings, inventory);
    
    return count_beacon_slots(readings, row);
}

int part_a(const std::string &inventory) {
    return count_beacon_slots(inventory, 2000000);
}

long long find_tuning_frequency(const std::string &inventory, const int &max ) {
    std::vector<std::pair<Location, Location>> readings;
    parse_inventory(readings, inventory);
    
    // we're going to run from row 0 to row 4000000
    // and find the row which has a space in it.

    std::vector<std::pair<int, int>> ranges;
    std::set<Location> beacons;

    int y;
    for(y = 0; y <= max; y++) {
        get_covered_ranges_and_beacons_on_row(readings, y, ranges, beacons);

        if (not std::any_of(ranges.begin(), ranges.end(), [&max]( auto r ) { return r.first <= 0 and r.second >= max; }))
            break;

        ranges.clear();
        beacons.clear();
    }

    auto r = ranges.begin();
    while( r < ranges.end() ) {
        if( r->first < 0 and r->second > 0 )
            break;
    }
    int x = r->second + 1;

    return (long long)x * 4000000 + (long long)y;
}

int part_b(const std::string &inventory) {
    long long x = find_tuning_frequency(inventory, 4000000);
    std::cout << x << std::endl;
    return 0;
}

} // namespace aoc