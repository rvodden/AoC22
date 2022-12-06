from aoc.day_03 import day_03a, day_03b

EXAMPLE = """vJrwpWtwJgWrhcsFMMfFFhFp
jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
PmmdzqPrVvPwwTWBwg
wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
ttgJtRGJQctTZtZT
CrZsJsPPZsGzwwsLwLmpwMDw"""

def test_day_03a():
    assert day_03a(EXAMPLE) == 157

def test_day_03b():
    assert day_03b(EXAMPLE) == 70

def test_day_03():
    with open("data/day03.txt") as file:
        data = file.read()
    assert day_03a(data) == 8153
    assert day_03b(data) == 2342