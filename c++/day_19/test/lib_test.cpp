#include <string>
#include <gtest/gtest.h>


#include "lib.hpp"

const std::string example(R"EOS(Blueprint 1: Each ore robot costs 4 ore. Each clay robot costs 2 ore. Each obsidian robot costs 3 ore and 14 clay. Each geode robot costs 2 ore and 7 obsidian.
Blueprint 2: Each ore robot costs 2 ore. Each clay robot costs 3 ore. Each obsidian robot costs 3 ore and 8 clay. Each geode robot costs 3 ore and 12 obsidian.)EOS");

TEST(day_19a, example) {
    EXPECT_EQ(aoc::part_a(example), 33);
}
