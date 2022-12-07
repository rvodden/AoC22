from collections import deque
from functools import reduce
import re

regex = r"move (\d+) from (\d+) to (\d+)"

def day_05a(example: str) -> str:
    lines = example.splitlines();
    length_of_line = len(lines[0])
    number_of_crates = (length_of_line + 1) // 4

    crates = [deque() for _ in range(number_of_crates)]

    filling = True

    for line in lines:
        if filling:
            if line == "":
                filling = False
                continue
            for crate_number, character in enumerate(line[1::4]):
                if character != " ":
                    crates[crate_number].appendleft(character)
            continue

        matches = re.match(regex, line);
        quantity, source, destination = map(int, matches.group(1,2,3))
        source -= 1  # crates are zero indexed
        destination -= 1 

        for _ in range(quantity):
            thing = crates[source].pop();
            crates[destination].append(thing);
        
    return ''.join([crate[-1] for crate in crates])


def day_05b(example: str) -> str:
    lines = example.splitlines();
    length_of_line = len(lines[0])
    number_of_crates = (length_of_line + 1) // 4

    crates = [deque() for _ in range(number_of_crates)]

    filling = True

    for line in lines:
        if filling:
            if line == "":
                filling = False
                continue
            for crate_number, character in enumerate(line[1::4]):
                if character != " ":
                    crates[crate_number].appendleft(character)
            continue

        matches = re.match(regex, line);
        quantity, source, destination = map(int, matches.group(1,2,3))
        source -= 1  # crates are zero indexed
        destination -= 1 

        things = deque()
        for _ in range(quantity):
            things.appendleft(crates[source].pop());
            
        for thing in things:
            crates[destination].append(thing);
        
    return ''.join([crate[-1] for crate in crates])
