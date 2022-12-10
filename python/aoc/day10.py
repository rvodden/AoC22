from itertools import accumulate, chain, islice
from math import prod

def batched(iterable, n):
    "Batch data into lists of length n. The last batch may be shorter."
    # batched('ABCDEFG', 3) --> ABC DEF G
    if n < 1:
        raise ValueError('n must be at least one')
    it = iter(iterable)
    while (batch := list(islice(it, n))):
        yield batch

def day10a(example: str) -> int:
    return sum(
        map(prod, 
            islice(
                enumerate(
                    accumulate(
                        chain([1], *[[0] if l == "noop" else [0, int(l[5:])] for l in example.splitlines()])
                    )
                , 1),
            19, None, 40
        ))
    )

def day10b(example: str) -> str:
    xs = list(accumulate(chain([1], *[[0] if l == "noop" else [0, int(l[5:])] for l in example.splitlines()])))
    xs.pop()
    chrs = ["#" if abs(x - (idx % 40)) <= 1 else "." for idx, x in enumerate(xs)]
    return "\n".join(map(''.join,batched(chrs, 40)))