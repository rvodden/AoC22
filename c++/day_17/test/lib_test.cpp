#include <string>
#include <gtest/gtest.h>


#include "lib.hpp"

using namespace aoc;

const std::string example(R"EOS(>>><<><>><<<>><>>><<<>>><<<><<<>><>><<>>)EOS");
const std::string example2(R"EOS(><>)EOS");

TEST(day_17a, unit) {
    Cycler<std::vector, char> cycler({'1','2','3'});
    EXPECT_EQ(cycler.next(), '1');
    EXPECT_EQ(cycler.next(), '2');
    EXPECT_EQ(cycler.next(), '3');
    EXPECT_EQ(cycler.next(), '1');
    EXPECT_EQ(cycler.next(), '2');
    EXPECT_EQ(cycler.next(), '3');
    
}

TEST(day_17a, example) {
    EXPECT_EQ(aoc::part_a(example), 3068);
}

TEST(day_17b, example) {
    EXPECT_EQ(aoc::part_b(example), 1514285714288);
}