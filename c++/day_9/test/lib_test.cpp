#include <string>
#include <gtest/gtest.h>


#include "lib.hpp"

const std::string example{R"EOS(R 4
U 4
L 3
D 1
R 4
D 1
L 5
R 2)EOS"};

const std::string example2(R"EOS(R 5
U 8
L 8
D 3
R 17
D 10
L 25
U 20)EOS");

TEST(Day9aTest, Example) {
    EXPECT_EQ(aoc::part_a(example), 13);
}

TEST(Day9bTest, Example) {
    EXPECT_EQ(aoc::part_b(example), 1);
    EXPECT_EQ(aoc::part_b(example2), 36);
}