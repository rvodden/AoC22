from aoc.day_05 import day_05a, day_05b

EXAMPLE="""    [D]    
[N] [C]    
[Z] [M] [P]
 1   2   3 

move 1 from 2 to 1
move 3 from 1 to 3
move 2 from 2 to 1
move 1 from 1 to 2
"""

def test_day_05a():
    assert day_05a(EXAMPLE) == "CMZ"

def test_day_05b():
    assert day_05b(EXAMPLE) == "MCD"

def test_day_05():
    with open("data/day05.txt") as file:
        data = file.read()
    assert day_05a(data) == "QMBMJDFTD"
    assert day_05b(data) == "NBTVTJNFJ"