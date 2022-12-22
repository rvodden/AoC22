#include <functional>
#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

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

    void turn(const Direction &d);
    void move(int64_t);
    int64_t password() const;
    void print_location() const { std::cout << _location << std::endl; };
    void print_map() const;

    inline std::pair<Location, Orientation> get_position() const { return std::make_pair(_location, _orientation); };
    inline void set_position(const Location &l, const Orientation &o) {_location = l; _orientation = o; };
  private:
    void wrap_around(const Location &delta);
    Location find_start_location() const;
    
    Location _location;
    Orientation _orientation = Orientation::RIGHT;
    const Map &_map;
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

using Face = char;
using Walk = std::tuple<Face, Edge, Bearing>; // this needs a different name
using Net = std::map<std::tuple<Walk, Walk>;
using NetScaling = std::map<Face,std::pair<Location,Location>>;
using WrapAround = std::unordered_map<Location, Location, PairHash>;

const NetScaling EXAMPLE_NET_SCALING = {
    { 1, {  8,  0 }, { 11,  3 } },
    { 2, {  0,  4 }, {  3,  7 } },
    { 3, {  4,  4 }, {  7,  7 } },
    { 4, {  8,  4 }, { 11,  7 } },
    { 5, {  8,  8 }, { 11, 11 } },
    { 6, {  8, 12 }, { 11, 15 } }
};

const Net EXAMPLE_NET = {
    {{1, Edge::EAST,  Bearing::ASCENDING }, {3, Edge::EAST,  Bearing::DESCENDING }},
    {{1, Edge::NORTH, Bearing::ASCENDING }, {2, Edge::NORTH, Bearing::DESCENDING }},
    {{1, Edge::EAST,  Bearing::ASCENDING }, {6, Edge::EAST,  Bearing::DESCENDING }},
    {{4, Edge::EAST,  Bearing::ASCENDING }, {6, Edge::NORTH, Bearing::DESCENDING }},
    {{6, Edge::SOUTH, Bearing::ASCENDING }, {5, Edge::SOUTH, Bearing::DESCENDING }},
    {{5, Edge::SOUTH, Bearing::DESCENDING}, {3, Edge::SOUTH, Bearing::ASCENDING  }},
    {{5, Edge::WEST,  Bearing::DESCENDING}, {3, Edge::SOUTH, Bearing::DESCENDING }}
};

int part_a(const std::string &inventory);
int part_b(const std::string &inventory);

}