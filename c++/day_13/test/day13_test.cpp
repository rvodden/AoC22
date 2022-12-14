#include <string>
#include <vector>
#include <gtest/gtest.h>


#include "day13.hpp"

const std::string example{R"EOS([1,1,3,1,1]
[1,1,5,1,1]

[[1],[2,3,4]]
[[1],4]

[9]
[[8,7,6]]

[[4,4],4,4]
[[4,4],4,4,4]

[7,7,7,7]
[7,7,7]

[]
[3]

[[[]]]
[[]]

[1,[2,[3,[4,[5,6,7]]]],8,9]
[1,[2,[3,[4,[5,6,0]]]],8,9])EOS"};

using V = std::vector<aoc::List>;

class Day13a : public testing::TestWithParam<std::tuple<aoc::List, aoc::List, bool>> {

};

TEST_P(Day13a, example) {
    aoc::List a = std::get<0>(GetParam());
    aoc::List b = std::get<1>(GetParam());
    bool result = std::get<2>(GetParam());

    EXPECT_EQ(aoc::correct_order(a, b), result);
};

INSTANTIATE_TEST_SUITE_P(ParamTests, Day13a, testing::Values( 
    std::make_tuple(V{1,1,3,1,1}, V{1,1,5,1,1}, true),
    std::make_tuple(V{V{1},V{2,3,4}}, V{V{1},4}, true),
    std::make_tuple(V{9}, V{V{8,7,6}}, false),
    std::make_tuple(V{V{4,4},4,4}, V{V{4,4},4,4,4}, true),
    std::make_tuple(V{7,7,7,7}, V{7,7,7}, false),
    std::make_tuple(V{}, V{3}, true),
    std::make_tuple(V{V{V{}}}, V{V{}}, false)
));

TEST(day_13a, example) {
    aoc::List a = V{1,2,3};
    EXPECT_EQ(aoc::parse_list("[1,2,3]"), a);

    a = V{1,2,V{3,4},5};
    EXPECT_EQ(aoc::parse_list("[1,2,[3,4],5]"), a);
    
    EXPECT_EQ(aoc::part_a(example), 13);
}

TEST(day_13b, example) {
    EXPECT_EQ(aoc::part_b(example), 140);
}