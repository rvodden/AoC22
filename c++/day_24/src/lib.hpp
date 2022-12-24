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


enum class Bearing{
    NORTH,
    EAST,
    SOUTH,
    WEST,
    NONE
};

using Location = std::pair<int64_t, int64_t>;
using TemporalLocation = std::pair<Location, uint64_t>;

const std::unordered_map<Bearing, Location> NEIGHBOURS {
    {Bearing::NORTH, {0,-1}},
    {Bearing::EAST, {1,0}},
    {Bearing::SOUTH, {0,1}},
    {Bearing::WEST, {-1,0}},
    {Bearing::NONE, {0,0}},
};

struct PairHash {
    template <typename T1, typename T2>
    size_t operator()(const std::pair<T1, T2> &pr) const {
        using std::hash;
        return hash<T1>()(pr.first) ^ hash<T2>()(pr.second);
    }
};

struct PairPairHash {
    template <typename T1, typename T2, typename T3>
    size_t operator()(const std::pair<std::pair<T1, T2>, T3> &pr) const {
        using std::hash;
        return hash<T1>()(pr.first.first) ^ hash<T2>()(pr.first.second) ^ hash<T3>()(pr.second);
    }
};

using StepSet = std::unordered_set<Location, PairHash>;
using TemporalStepSet = std::unordered_set<TemporalLocation, PairPairHash>;
using Map = std::unordered_multimap<Location, Bearing, PairHash>;

bool operator==(const Location &l, const Location &r);
Location operator+(const Location &l, const Location &r);
Location operator-(const Location &l, const Location &r);
Location operator*(const Location &l, const int64_t &r);
Location& operator+=(Location &l, const Location &r);
std::ostream& operator<<(std::ostream& s, const Location &l);


class State {
  public:
    explicit State(const Map &m, const Location &e) : map(m), extents(e) { };

    void print_map() const;
    void print_map(const Location &location) const;
    Location next_position() const;
    void move();

    Map map;
    Location extents;
};

Location parse_input(Map &map, const std::string &input);

int part_a(const std::string &inventory);
int part_b(const std::string &inventory);

}