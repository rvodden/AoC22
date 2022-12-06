#include <string>
#include <gtest/gtest.h>


#include "day_5a.hpp"

const std::string example{R"EOS(    [D]    
[N] [C]    
[Z] [M] [P]
 1   2   3 

move 1 from 2 to 1
move 3 from 1 to 3
move 2 from 2 to 1
move 1 from 1 to 2)EOS"};

TEST(Day5aTest, Example) {
    EXPECT_TRUE(aoc::day_5a(example) == "CMZ");
}