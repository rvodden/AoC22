#include <functional>
#include <string>
#include <sstream>
#include <vector>

namespace aoc {

int count_beacon_slots(const std::string &inventory, const int &row);
long long find_tuning_frequency(const std::string &inventory, const int &row);

int part_a(const std::string &inventory);
int part_b(const std::string &inventory);

}