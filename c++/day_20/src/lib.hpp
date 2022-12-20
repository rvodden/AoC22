#include <functional>
#include <string>
#include <sstream>
#include <unordered_set>
#include <vector>

#include <list>

namespace aoc {

int part_a(const std::string &inventory);
int part_b(const std::string &inventory);

void step(std::list<std::pair<int64_t, std::size_t>> &working_list, const std::list<std::pair<int64_t, std::size_t>>::iterator &p, const int64_t list_size);
std::list<std::pair<int64_t, std::size_t>>::iterator next_position(std::list<std::pair<int64_t,std::size_t>> &l, const std::size_t &i);
void mix(std::list<std::pair<int64_t, std::size_t>> &working_list);
void apply_encryption_key( const std::vector<int64_t> &input_list, std::list<std::pair<int64_t, std::size_t>> &working_list );

}