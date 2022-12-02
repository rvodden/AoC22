#include <string>
#include <gtest/gtest.h>

#include "day_1a.hpp"

std::string example = R"EOS(1000
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

    aoc::CalorieCounter calorie_counter;
    EXPECT_EQ(calorie_counter.day_1(example), 24000);

};

