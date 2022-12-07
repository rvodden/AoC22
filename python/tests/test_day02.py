from aoc.day02 import day_02a, day_02b

EXAMPLE = """A Y
B X
C Z
"""

def test_day_02a():
    assert day_02a(EXAMPLE) == 15

def test_day_02b():
    assert day_02b(EXAMPLE) == 12

def test_day_02():
    with open("data/day02.txt") as file:
        data = file.read()
    assert day_02a(data) == 12679
    assert day_02b(data) == 14470