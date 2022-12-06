def day_01a(example: str) -> int:
    return max([sum([int(i) for i in t.splitlines()]) for t in example.split("\n\n")])

def day_01b(example: str) -> int:
    return sum(sorted([sum([int(i) for i in t.splitlines()]) for t in example.split("\n\n")])[-3:])