from aoc.day07 import day07a, day07b

EXAMPLE = """$ cd /
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
7214296 k"""

def test_day07a():
    assert day07a(EXAMPLE) == 95437

def test_day07b():
    assert day07b(EXAMPLE) == 24933642

def test_day07():
    with open("data/day07.txt") as file:
        data = file.read()
    assert day07a(data) == 1315285
    assert day07b(data) == 9847279