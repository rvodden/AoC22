#include <string>
#include <list>
#include <utility>

#include <gtest/gtest.h>


#include "lib.hpp"

using namespace aoc;

const std::string example(R"EOS(#.######
#>>.<^<#
#.<..<<#
#>v.><>#
#<^v^^>#
######.#)EOS");

TEST(day_24a, example) {
    EXPECT_EQ(aoc::part_a(example), 18);
}

TEST(day_24b, example) {
    EXPECT_EQ(aoc::part_b(example), 54);
}