from aoc.day_01 import day_01a, day_01b

EXAMPLE = """1000
2000
3000

4000

5000
6000

7000
8000
9000

10000"""

def test_day_01_a():
    assert day_01a(EXAMPLE) == 24000

def test_day_01_b():
    assert day_01b(EXAMPLE) == 45000

def test_day_01():
    with open("data/day01.txt") as file:
        data = file.read()
    assert day_01a(data) == 66616
    assert day_01b(data) == 199172