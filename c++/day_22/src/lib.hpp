#include <functional>
#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <variant>

#include <list>

namespace aoc {

enum class Direction {
    LEFT = 'L',
    RIGHT = 'R'
};

enum class Orientation {
    RIGHT = 0,
    DOWN = 1,
    LEFT = 2,
    UP = 3
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

using Location = std::pair<int64_t, int64_t>;
using Map = std::unordered_map<Location, bool, PairHash>;
using Step = std::variant<Direction, int64_t>;
using Route = std::queue<Step>;


bool operator==(const Location &l, const Location &r);
Location operator+(const Location &l, const Location &r);
Location operator*(const Location &l, const int64_t &r);
Location& operator+=(Location &l, const Location &r);
std::ostream& operator<<(std::ostream& s, const Location &l);

class State {
  public:
    explicit State(const Map &map) : _map(map) {
        _location = find_start_location();
    };

    virtual ~State() = default;

    void turn(const Direction &d);
    void move(int64_t);
    int64_t password() const;
    void print_location() const { std::cout << _location << std::endl; };
    void print_map() const;

    inline std::pair<Location, Orientation> get_position() const { return std::make_pair(_location, _orientation); };
    inline void set_position(const Location &l, const Orientation &o) {_location = l; _orientation = o; };

  protected:
    virtual void wrap_around(const Location &delta);
    Location _location;
    const Map &_map;
    Location find_start_location() const;
    Orientation _orientation = Orientation::RIGHT;
};


void parse_map(Map &map, const std::string &input);
void parse_route(Route &route, const std::string &input);

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

using Face = uint8_t;
using Walk = std::tuple<Face, Edge, Bearing>; // this needs a different name
using Net = std::vector<std::pair<Walk, Walk>>;
using Range = std::pair<Location,Location>;
using NetScaling = std::map<Face,Range>;
using WrapAround = std::unordered_map<std::pair<Location, Orientation>, std::pair<Location, Orientation>, PairPairHash>;

const NetScaling EXAMPLE_NET_SCALING = {
    { 1, {{  8, 0 }, { 11,  3 }} },
    { 2, {{  0, 4 }, {  3,  7 }} },
    { 3, {{  4, 4 }, {  7,  7 }} },
    { 4, {{  8, 4 }, { 11,  7 }} },
    { 5, {{  8, 8 }, { 11, 11 }} },
    { 6, {{ 12, 8 }, { 15, 11 }} }
};

const Net EXAMPLE_NET = {
    {{1, Edge::EAST,  Bearing::ASCENDING }, {6, Edge::EAST,  Bearing::DESCENDING }},
    {{1, Edge::NORTH, Bearing::ASCENDING }, {2, Edge::NORTH, Bearing::DESCENDING }},
    {{1, Edge::WEST,  Bearing::ASCENDING }, {3, Edge::NORTH, Bearing::ASCENDING  }},
    {{4, Edge::EAST,  Bearing::ASCENDING }, {6, Edge::NORTH, Bearing::DESCENDING }},
    {{2, Edge::EAST,  Bearing::ASCENDING }, {6, Edge::SOUTH, Bearing::DESCENDING }},
    {{2, Edge::SOUTH, Bearing::ASCENDING }, {5, Edge::SOUTH, Bearing::DESCENDING }},
    {{3, Edge::SOUTH, Bearing::ASCENDING }, {5, Edge::EAST,  Bearing::DESCENDING }},
};

const NetScaling INPUT_NET_SCALING = {
    { 1, {{  50,  0  }, {  99,  49 }} },
    { 2, {{ 100,  0  }, { 149,  49 }} },
    { 3, {{  50, 50  }, {  99,  99 }} },
    { 4, {{   0, 100 }, {  49, 149 }} },
    { 5, {{  50, 100 }, {  99, 149 }} },
    { 6, {{   0, 150 }, {  49, 199 }} }
};

const Net INPUT_NET = {
    {{1, Edge::WEST,  Bearing::ASCENDING }, {4, Edge::WEST,  Bearing::DESCENDING }},
    {{1, Edge::NORTH, Bearing::ASCENDING }, {6, Edge::WEST,  Bearing::ASCENDING  }},
    {{2, Edge::SOUTH, Bearing::ASCENDING }, {3, Edge::EAST,  Bearing::ASCENDING  }},
    {{2, Edge::EAST,  Bearing::ASCENDING }, {5, Edge::EAST,  Bearing::DESCENDING }},
    {{2, Edge::NORTH, Bearing::ASCENDING }, {6, Edge::SOUTH, Bearing::ASCENDING  }},
    {{3, Edge::WEST,  Bearing::ASCENDING }, {4, Edge::NORTH, Bearing::ASCENDING  }},
    {{5, Edge::SOUTH, Bearing::ASCENDING }, {6, Edge::EAST,  Bearing::ASCENDING  }}
};

class PartTwoState : public State {
  public:
    PartTwoState(const Map &map, const WrapAround &wrap_around) : State(map), _wrap_around(wrap_around) {};

  private:
    void wrap_around(const Location &delta) override;
    const WrapAround _wrap_around;
};

void generate_edge_mappings(const Net &net, const NetScaling &net_scaling, WrapAround &wrap_around);
int64_t calculate_cube_journey(const std::string &input, const Net &net, const NetScaling &net_scaling);

int part_a(const std::string &inventory);
int64_t part_b(const std::string &inventory);

}