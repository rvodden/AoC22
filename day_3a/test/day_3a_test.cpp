#include <string>
#include <gtest/gtest.h>


#include "day_3a.hpp"

const std::string example{R"EOS(vJrwpWtwJgWrhcsFMMfFFhFp
jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
PmmdzqPrVvPwwTWBwg
wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
ttgJtRGJQctTZtZT
CrZsJsPPZsGzwwsLwLmpwMDw)EOS"};

TEST(Day3aTest, Example) {
    EXPECT_EQ(aoc::day_3a(example), 157);
}