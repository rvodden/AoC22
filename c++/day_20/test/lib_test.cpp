#include <string>
#include <list>
#include <utility>

#include <gtest/gtest.h>


#include "lib.hpp"

using namespace aoc;

const std::string example(R"EOS(1
2
-3
3
-2
0
4)EOS");

TEST(day_20a, unit) {

    std::list<std::pair<int64_t, std::size_t>> list = {{1,0},{ 2, 1}, {-3,2}, {3,3}, {-2,4}, {0,5}, {4,6}};
    std::size_t list_size = 7;

    auto p = next_position(list, 0);
    step(list, p, list_size);
    std::list<std::pair<int64_t, std::size_t>> t({{2,1}, {1,0}, {-3,2}, {3,3}, {-2,4}, {0,5}, {4,6}});
    EXPECT_EQ(list, t);

    p = next_position(list, 1);
    step(list, p, list_size);
    t = {{1,0},{-3,2},{2,1},{3,3},{-2,4},{0,5},{4,6}};
    EXPECT_EQ(list, t);
    
    p = next_position(list, 2);
    step(list, p, list_size);
    t = {{1,0},{2,1},{3,3},{-2,4},{-3,2},{0,5},{4,6}};
    EXPECT_EQ(list, t);
    
    p = next_position(list, 3);
    step(list, p, list_size);
    t = {{1,0},{2,1},{-2,4},{-3,2},{0,5},{3,3},{4,6}};
    EXPECT_EQ(list, t);
    
    p = next_position(list, 4);
    step(list, p, list_size);
    t = {{1,0},{2,1},{-3,2},{0,5},{3,3},{4,6},{-2,4}};
    EXPECT_EQ(list, t);
    
    p = next_position(list, 5);
    step(list, p, list_size);
    t = {{1,0},{2,1},{-3,2},{0,5},{3,3},{4,6},{-2,4}};
    EXPECT_EQ(list, t);
    
    p = next_position(list, 6);
    step(list, p, list_size);
    t = {{1,0},{2,1},{-3,2},{4,6},{0,5},{3,3},{-2,4}};
    EXPECT_EQ(list, t);
}

std::list<int64_t> list_of_values(const std::list<std::pair<int64_t, std::size_t>> &list) {
    std::list<int64_t> retval(list.size());
    std::transform(list.begin(), list.end(), retval.begin(), [](const auto &t){ return t.first; });
    return retval;
}

TEST(day_20a, unit2) {
    std::vector<int64_t> input = {1,2,-3,3,-2,0,4};
    std::list<std::pair<int64_t, std::size_t>> list;

    using V = std::list<int64_t>;
    std::array<std::list<int64_t>,11> expected(
        {
        V{811589153, 1623178306, -2434767459, 2434767459, -1623178306, 0, 3246356612},
        V{0, -2434767459, 3246356612, -1623178306, 2434767459, 1623178306, 811589153},
        V{0, 2434767459, 1623178306, 3246356612, -2434767459, -1623178306, 811589153},
        V{0, 811589153, 2434767459, 3246356612, 1623178306, -1623178306, -2434767459},
        V{0, 1623178306, -2434767459, 811589153, 2434767459, 3246356612, -1623178306},
        V{0, 811589153, -1623178306, 1623178306, -2434767459, 3246356612, 2434767459},
        V{0, 811589153, -1623178306, 3246356612, -2434767459, 1623178306, 2434767459},
        V{0, -2434767459, 2434767459, 1623178306, -1623178306, 811589153, 3246356612},
        V{0, 1623178306, 3246356612, 811589153, -2434767459, 2434767459, -1623178306},
        V{0, 811589153, 1623178306, -2434767459, 3246356612, 2434767459, -1623178306},
        V{0, -2434767459, 1623178306, 3246356612, -1623178306, 2434767459, 811589153}}
        );

    apply_encryption_key(input, list);
    EXPECT_EQ(list_of_values(list), expected[0]);

    for(char k = 1; k <= 10; k++) {
        mix(list);
        EXPECT_EQ(list_of_values(list), expected[k]);
    }
}

TEST(day_20a, example) {
    EXPECT_EQ(aoc::part_a(example), 3);
}

TEST(day_20b, example) {
    EXPECT_EQ(aoc::part_b(example), 1623178306);
}