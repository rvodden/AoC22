from aoc.day04 import day_04a, day_04b

EXAMPLE="""2-4,6-8
2-3,4-5
5-7,7-9
2-8,3-7
6-6,4-6
2-6,4-8"""

def test_day_04a():
    assert day_04a(EXAMPLE) == 2


def test_day_04():
    with open("data/day04.txt") as file:
        data = file.read()
    assert day_04a(data) == 509
    assert day_04b(data) == 870