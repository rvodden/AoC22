#include <algorithm>
#include <string>
#include <vector>

#include "day_6a.hpp"

namespace aoc {

int day_6a(const std::string &inventory) {
    auto start_slice = inventory.begin();
    auto end_slice = inventory.begin();
    std::advance(end_slice, 4);

    int start_of_packet = 4;

    do {
        std::vector<char> packet(start_slice, end_slice);
        std::sort(packet.begin(), packet.end());
        if ( std::adjacent_find(packet.begin(), packet.end()) == packet.end() ) {
            break;
        }
        start_of_packet++;
        start_slice++;
        end_slice++;
    } while(end_slice != inventory.end());

    return start_of_packet;
}

} // namespace aoc