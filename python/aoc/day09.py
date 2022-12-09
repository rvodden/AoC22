from itertools import pairwise, chain

DIR = {
    "L": (-1 , 0),
    "R": (1, 0),
    "U": (0, 1),
    "D": (0, -1)
}

def adjascent(d: tuple[int, int]) -> bool:
    return max(map(abs, d)) <= 1

def normalize(d: tuple[int, int]) -> tuple[int, int]:
    def n(d: int) -> int:
        return 0 if d == 0 else d // abs(d);

    return tuple(map(n, d))

def add(l: tuple[int, int], r: tuple[int, int]) -> tuple[int, int]:
    return (l[0] + r[0], l[1] + r[1])

def subtract(l: tuple[int, int], r: tuple[int, int]) -> tuple[int, int]:
    return (l[0] - r[0], l[1] - r[1])

def day09a(example: str) -> int:
    lines = example.splitlines()
    head = (0,0)
    tail = (0,0)
    tail_visited_locations = set()
    tail_visited_locations.add(tail)
    
    for dir in chain(*[[DIR[x]] * int(u) for x, u in map(lambda x: x.split(), lines)]):
        head = add(head, dir)
        tail = tail if adjascent(subtract(head, tail)) else add(tail, normalize(subtract(head, tail)))
        tail_visited_locations.add(tail)
    return len(tail_visited_locations)

def day09b(example: str) -> int:
    lines = example.splitlines()
    tail_visited_locations = set()
    rope = [(0,0) for _ in range(10)]
    tail_visited_locations.add(rope[-1])
    
    for dir in chain(*[[DIR[x]] * int(u) for x, u in map(lambda x: x.split(), lines)]):
        rope[0] = add(rope[0], dir)
        for i, j in pairwise(range(10)):
            rope[j] = rope[j] if adjascent(subtract(rope[i], rope[j])) else add(rope[j], normalize(subtract(rope[i], rope[j])))
        tail_visited_locations.add(rope[-1])
    return len(tail_visited_locations)