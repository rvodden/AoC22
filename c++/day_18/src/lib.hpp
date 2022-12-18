#include <functional>
#include <string>
#include <sstream>
#include <unordered_set>
#include <vector>

namespace aoc {

int part_a(const std::string &inventory);
int part_b(const std::string &inventory);

using Location = std::tuple<int,int,int>;

struct LocationHash {
    std::size_t operator()(const Location &l) const noexcept {
        return std::get<0>(l) * 1001 + std::get<1>(l) * 1011 + std::get<2>(l) * 1019;
    }
};

using Locations = std::unordered_set<Location, LocationHash>;

bool can_escape(const Locations &solid, const Location &location, const std::pair<Location, Location> &bounds, Locations &visited );
void get_bounds_of_solid(const Locations &solid, Location &upper, Location &lower);

}