#include <string>
#include <list>
#include <utility>

#include <gtest/gtest.h>


#include "lib.hpp"

using namespace aoc;

const std::string example(R"EOS(        ...#
        .#..
        #...
        ....
...#.......#
........#...
..#....#....
..........#.
        ...#....
        .....#..
        .#......
        ......#.

10R5L5R10L4R5L5)EOS");

const std::string example_map_string(R"EOS(        ...#
        .#..
        #...
        ....
...#.......#
........#...
..#....#....
..........#.
        ...#....
        .....#..
        .#......
        ......#.)EOS");


namespace aoc {
TEST(day_22a, unit) {
    Map map;
    parse_map(map, example_map_string);

    State state(map);

    state.set_position({11,7}, Orientation::RIGHT);
    state.move(1);
    const auto &[l, o] = state.get_position();
    EXPECT_EQ(l, std::make_pair(0L,7L));
    
    state.set_position({5, 7}, Orientation::DOWN);
    state.move(1);
    const auto &m = state.get_position().first;
    EXPECT_EQ(m, std::make_pair(5L,4L));
    
    state.set_position({5, 7}, Orientation::DOWN);
    state.move(2);
    const auto &n = state.get_position().first;
    EXPECT_EQ(n, std::make_pair(5L,5L));
};


TEST(day_22a, unit2) {
    WrapAround wrap_around;
    generate_edge_mappings(EXAMPLE_NET, EXAMPLE_NET_SCALING, wrap_around);

    Map map;
    parse_map(map, example_map_string);

    PartTwoState state(map, wrap_around);

    state.set_position({11,5}, Orientation::RIGHT);
    state.move(1);
    const auto &[k, l] = state.get_position();
    EXPECT_EQ(k, std::make_pair(14L,8L));
    EXPECT_EQ(l, Orientation::DOWN);
    
    state.set_position({10, 11}, Orientation::DOWN);
    state.move(1);
    const auto &[m, n] = state.get_position();
    EXPECT_EQ(m, std::make_pair(1L,7L));
    EXPECT_EQ(n, Orientation::UP);
    
    state.set_position({6, 4}, Orientation::UP);
    state.move(1);
    const auto &[o, p] = state.get_position();
    EXPECT_EQ(o, std::make_pair(6L,4L));
    EXPECT_EQ(p, Orientation::UP);
};
}

TEST(day_22a, example) {
    EXPECT_EQ(part_a(example), 6032);
}

TEST(day_22b, example) {
    EXPECT_EQ(calculate_cube_journey(example, EXAMPLE_NET, EXAMPLE_NET_SCALING), 5031);
}