#include <string>
#include <gtest/gtest.h>

#include "day_2a.hpp"

const std::string example = R"EOS(A Y
B X
C Z
)EOS";


TEST(Day1bTest, Example) {

    EXPECT_EQ(aoc::day_2a(example), 15);

};

