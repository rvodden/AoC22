#include <string>
#include <gtest/gtest.h>


#include "day_7.hpp"

const std::string example{R"EOS($ cd /
$ ls
dir a
14848514 b.txt
8504156 c.dat
dir d
$ cd a
$ ls
dir e
29116 f
2557 g
62596 h.lst
$ cd e
$ ls
584 i
$ cd ..
$ cd ..
$ cd d
$ ls
4060174 j
8033020 d.log
5626152 d.ext
7214296 k)EOS"};

TEST(Day7aTest, Example) {
    EXPECT_EQ(aoc::day_7a(example), 95437);
}

TEST(Day7bTest, Example) {
    EXPECT_EQ(aoc::day_7b(example), 24933642);
}