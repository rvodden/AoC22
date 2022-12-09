from aoc.day09 import day09a, day09b

EXAMPLE = """R 4
U 4
L 3
D 1
R 4
D 1
L 5
R 2"""

EXAMPLE2 = """R 5
U 8
L 8
D 3
R 17
D 10
L 25
U 20"""

def test_day09a():
    assert day09a(EXAMPLE) == 13

def test_day09b():
    assert day09b(EXAMPLE) == 1
    assert day09b(EXAMPLE2) == 36

def test_day09():
    with open("data/day09.txt") as file:
        data = file.read()
    assert day09a(data) == 6464
    assert day09b(data) == 2604