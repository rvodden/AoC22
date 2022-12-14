#include <memory>
#include <string>
#include <sstream>
#include <variant>
#include <vector>

namespace aoc {

class List;
class List : public std::variant<int, std::vector<List>> {
  public:
    using base = std::variant<int, std::vector<List>>;
    using base::base;
    using base::operator=;
};


// non-recursive definition 
// template<class T>
// using Var = std::variant<int, std::vector<T>>;

// // tie the knot
// template <template<class> class K>
// struct Fix : K<Fix<K>>
// {
//    using K<Fix>::K;
// };

// using List = Fix<Var>;

bool correct_order(const List &first, const List &second);
List parse_list(std::string str);

int part_a(const std::string &inventory);
int part_b(const std::string &inventory);

}