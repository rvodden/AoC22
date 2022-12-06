#include <string>
#include <gtest/gtest.h>


#include "day_6b.hpp"

class Day6bTest : public testing::TestWithParam<std::pair<std::string, int>> {

};

TEST_P(Day6bTest, Example) {
    std::string example = GetParam().first;
    int result = GetParam().second;

    EXPECT_EQ(aoc::day_6b(example), result);
};

INSTANTIATE_TEST_SUITE_P(ParamTests, Day6bTest, testing::Values( 
    std::make_pair("mjqjpqmgbljsphdztnvjfqwrcgsmlb", 19),
    std::make_pair("bvwbjplbgvbhsrlpgdmjqwftvncz", 23),
    std::make_pair("nppdvjthqldpwncqszvftbrmjlhg", 23),
    std::make_pair("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 29),
    std::make_pair("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", 26)
));