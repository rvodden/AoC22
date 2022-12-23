#include <string>
#include <list>
#include <utility>

#include <gtest/gtest.h>


#include "lib.hpp"

using namespace aoc;

const std::string example(R"EOS(....#..
..###.#
#...#.#
.#...##
#.###..
##.#.##
.#..#..)EOS");

const std::string example2(R"EOS(.....
..##.
..#..
.....
..##.
.....)EOS");


const aoc::Map example_map = {
    {0,0},
    {1,0},
    {0,1},
    {0,3},
    {1,3}
};

TEST(day_23a, unit) {
    aoc::Map em = example_map;
    aoc::State state(em);
    using L = aoc::Location;
    EXPECT_EQ(state.next_position(L{0,0}), L({0,-1}));
    EXPECT_EQ(state.next_position(L{1,0}), L({1,-1}));
    EXPECT_EQ(state.next_position(L{0,1}), L({0, 2}));
    EXPECT_EQ(state.next_position(L{0,3}), L({0, 2}));
    EXPECT_EQ(state.next_position(L{1,3}), L({1, 2}));

    state.move();

    for(const auto &i : Map({{0,-1},{1,-1},{0,1},{1,2},{0,3}})) {
        EXPECT_TRUE(state.get_map().contains(i));
    }
}

TEST(day_23a, example) {
    EXPECT_EQ(aoc::part_a(example), 110);
}

TEST(day_23b, example) {
    EXPECT_EQ(aoc::part_b(example), 20);
}