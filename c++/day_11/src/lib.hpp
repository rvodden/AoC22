#include <functional>
#include <string>
#include <sstream>
#include <vector>

namespace aoc {

class Monkey {
  public:
    std::vector<int> items;
    std::function<int(const int&)> opp;
    std::function<bool(const int&)> test;

    int monkey_if_true;
    int monkey_if_false;
    int count = 0;
};

int part_a(const std::string &inventory);
std::string part_b(const std::string &inventory);

}