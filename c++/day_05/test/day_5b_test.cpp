#include <string>
#include <gtest/gtest.h>


#include "day_5b.hpp"

const std::string example{R"EOS(    [D]    
[N] [C]    
[Z] [M] [P]
 1   2   3 

move 1 from 2 to 1
move 3 from 1 to 3
move 2 from 2 to 1
move 1 from 1 to 2)EOS"};

TEST(Day5bTest, Example) {
    EXPECT_TRUE(aoc::day_5b(example) == "MCD");
}