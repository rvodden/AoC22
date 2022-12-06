#include <string>
#include <gtest/gtest.h>


#include "day_3b.hpp"

const std::string example{R"EOS(vJrwpWtwJgWrhcsFMMfFFhFp
jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
PmmdzqPrVvPwwTWBwg
wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
ttgJtRGJQctTZtZT
CrZsJsPPZsGzwwsLwLmpwMDw)EOS"};

TEST(Day3bTest, Example) {
    EXPECT_EQ(aoc::day_3b(example), 70);
}