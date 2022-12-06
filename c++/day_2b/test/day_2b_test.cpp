#include <string>
#include <gtest/gtest.h>

#include "day_2b.hpp"

const std::string example = R"EOS(A Y
B X
C Z
)EOS";


TEST(Day2bTest, Example) {

    EXPECT_EQ(aoc::day_2b(example), 12);

};

