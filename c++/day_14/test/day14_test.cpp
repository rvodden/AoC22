#include <string>
#include <vector>
#include <gtest/gtest.h>


#include "day14.hpp"

const std::string example{R"EOS(498,4 -> 498,6 -> 496,6
503,4 -> 502,4 -> 502,9 -> 494,9)EOS"};

TEST(day_14a, example) {
    EXPECT_EQ(aoc::part_a(example), 24);
}

TEST(day_14b, example) {
    EXPECT_EQ(aoc::part_b(example), 93);
}