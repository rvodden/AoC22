#include <string>
#include <gtest/gtest.h>


#include "lib.hpp"

const std::string example{R"EOS(30373
25512
65332
33549
35390)EOS"};

TEST(Day8aTest, Example) {
    EXPECT_EQ(aoc::part_a(example), 21);
}

TEST(Day8bTest, Example) {
    EXPECT_EQ(aoc::part_b(example), 8);
}