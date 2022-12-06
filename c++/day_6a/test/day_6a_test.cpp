#include <string>
#include <gtest/gtest.h>


#include "day_6a.hpp"

class Day6aTest : public testing::TestWithParam<std::pair<std::string, int>> {

};

TEST_P(Day6aTest, Example) {
    std::string example = GetParam().first;
    int result = GetParam().second;

    EXPECT_EQ(aoc::day_6a(example), result);
};

INSTANTIATE_TEST_SUITE_P(ParamTests, Day6aTest, testing::Values( 
    std::make_pair("mjqjpqmgbljsphdztnvjfqwrcgsmlb", 7),
    std::make_pair("bvwbjplbgvbhsrlpgdmjqwftvncz", 5),
    std::make_pair("nppdvjthqldpwncqszvftbrmjlhg", 6),
    std::make_pair("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 10),
    std::make_pair("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", 11)
));