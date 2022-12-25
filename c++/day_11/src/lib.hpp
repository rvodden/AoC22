#include <functional>
#include <string>
#include <sstream>
#include <vector>

namespace aoc {

class Monkey {
  public:
    std::vector<int64_t> items;
    std::function<int64_t(const int64_t&)> opp;
    std::function<bool(const int64_t&)> test;

    int64_t monkey_if_true;
    int64_t monkey_if_false;
    int64_t divisor;
    int64_t count = 0;
};

int64_t part_a(const std::string &inventory);
int64_t part_b(const std::string &inventory);

}