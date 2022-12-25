#include <stack>
#include <string>

namespace aoc {

using Snafu = std::stack<int8_t>;

int64_t snafu_to_int(const Snafu&);
int64_t snafu_to_int(const std::string&);

Snafu int_to_snafu(const int64_t&);
std::string int_to_snafu_string(const int64_t&);

std::string part_a(const std::string &inventory);
int part_b(const std::string &inventory);

}