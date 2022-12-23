#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <list>

namespace aoc {

enum class Direction {
    N,
    NE,
    E,
    SE,
    S,
    SW,
    W,
    NW
};

using Location = std::pair<int64_t, int64_t>;

const std::unordered_map<Direction, Location> NEIGHBOURS {
    {Direction::N, {0,-1}},
    {Direction::NE, {1,-1}},
    {Direction::E, {1,0}},
    {Direction::SE, {1,1}},
    {Direction::S, {0,1}},
    {Direction::SW, {-1,1}},
    {Direction::W, {-1,0}},
    {Direction::NW, {-1,-1}},
};

struct PairHash {
    template <typename T1, typename T2>
    size_t operator()(const std::pair<T1, T2> &pr) const {
        using std::hash;
        return hash<T1>()(pr.first) ^ hash<T2>()(pr.second);
    }
};


using Map = std::unordered_set<Location, PairHash>;

bool operator==(const Location &l, const Location &r);
Location operator+(const Location &l, const Location &r);
Location operator*(const Location &l, const int64_t &r);
Location& operator+=(Location &l, const Location &r);
std::ostream& operator<<(std::ostream& s, const Location &l);

using Rule = std::pair<std::array<Direction, 3>, Direction>;
using Rules = std::vector<Rule>;

class State {
  public:
    explicit State(Map &map) : _map(map) {
        _rules = {
            {{Direction::N, Direction::NE, Direction::NW}, Direction::N},
            {{Direction::S, Direction::SE, Direction::SW}, Direction::S},
            {{Direction::W, Direction::NW, Direction::SW}, Direction::W},
            {{Direction::E, Direction::NE, Direction::SE}, Direction::E}
        };
    };

    void print_map() const;
    Location next_position(const Location&) const;
    bool move();
    int64_t score() const;
    const Map& get_map() const { return _map; };
    void rotate_rules();

  private:
    
    std::pair<Location, Location> get_extents() const;
    
    Map &_map;
    Rules _rules;
};

void parse_map(Map &map, const std::string &input);

enum class Edge {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

enum class Bearing {
    ASCENDING,
    DESCENDING
};

int part_a(const std::string &inventory);
int part_b(const std::string &inventory);

}