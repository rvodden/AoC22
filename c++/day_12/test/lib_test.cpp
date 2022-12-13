#include <string>
#include <gtest/gtest.h>


#include "lib.hpp"

const std::string example{R"EOS(Sabqponm
abcryxxl
accszExk
acctuvwj
abdefghi)EOS"};

TEST(day_12a, DISABLED_example) {
    EXPECT_EQ(aoc::part_a(example), 31);
}

TEST(day_12b, example) {
    EXPECT_EQ(aoc::part_b(example), 29);
}