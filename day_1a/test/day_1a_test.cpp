#include <string>
#include <gtest/gtest.h>

#include "day_1a.hpp"

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

    EXPECT_EQ(aoc::day_1a(example), 24000);

};

