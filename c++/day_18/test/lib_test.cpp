#include <string>
#include <gtest/gtest.h>


#include "lib.hpp"

using namespace aoc;

const std::string example(R"EOS(2,2,2
1,2,2
3,2,2
2,1,2
2,3,2
2,2,1
2,2,3
2,2,4
2,2,6
1,2,5
3,2,5
2,1,5
2,3,5
)EOS");

TEST(day_18a, example) {
    EXPECT_EQ(aoc::part_a(example), 64);
}

TEST(day_18b, example) {
    EXPECT_EQ(aoc::part_b(example), 58);
}