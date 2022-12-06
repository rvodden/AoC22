import pytest
from aoc.day_06 import day_06a, day_06b

EXAMPLES = [("mjqjpqmgbljsphdztnvjfqwrcgsmlb", 7),
    ("bvwbjplbgvbhsrlpgdmjqwftvncz", 5),
    ("nppdvjthqldpwncqszvftbrmjlhg", 6),
    ("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 10),
    ("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", 11)];

@pytest.mark.parametrize("example,expected", EXAMPLES)
def test_day_06(example: str, expected: int):
    assert day_06a(example) == expected

EXAMPLES_B = [("mjqjpqmgbljsphdztnvjfqwrcgsmlb", 19),
    ("bvwbjplbgvbhsrlpgdmjqwftvncz", 23),
    ("nppdvjthqldpwncqszvftbrmjlhg", 23),
    ("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 29),
    ("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", 26)];

@pytest.mark.parametrize("example,expected", EXAMPLES_B)
def test_day_06b(example: str, expected: int):
    assert day_06b(example) == expected
