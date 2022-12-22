#include <string>
#include <list>
#include <utility>

#include <gtest/gtest.h>


#include "lib.hpp"

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
}

TEST(day_22a, example) {
    EXPECT_EQ(aoc::part_a(example), 6032);
}

TEST(day_22b, DISABLED_example) {
    EXPECT_EQ(aoc::part_b(example), 301);
}