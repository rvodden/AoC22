#include <string>
#include <gtest/gtest.h>

#include "lib.hpp"

const std::string example = R"EOS(1000
2000
3000

4000

5000
6000

7000
8000
9000

10000
)EOS";


TEST(Day1aTest, Example) {

    EXPECT_EQ(aoc::part_a(example), 24000);

};

TEST(Day1bTest, Example) {

    EXPECT_EQ(aoc::part_b(example), 45000);

};