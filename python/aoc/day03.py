def score(char: str) -> int:
    s = ord(char)
    return s - 96 if 97 < s <= 122 else s - 38

def day_03a(example: str) -> int:
    return sum([ score(set(line[:len(line)//2]).intersection(set(line[len(line)//2:])).pop()) for line in example.splitlines()])

def day_03b(example: str) -> int:
    lines = example.splitlines()
    total = 0
    l = iter(lines)
    try:
        while True:
            l1, l2, l3 = next(l), next(l), next(l)
            total += score(set(l1).intersection(set(l2).intersection(set(l3))).pop())
    except StopIteration:
        return total
    