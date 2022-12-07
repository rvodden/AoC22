def day_04a(example: str) -> int:
    lines = example.splitlines()

    contained = 0
    for line in lines:
        left, right = [[int(i) for i in r.split("-")] for r in line.split(",")]
        if ( left[0]  <= right[0] and left[1] >= right[1] ) or \
           ( right[0] <= left[0] and right[1] >= left[1] ):
            contained += 1

    return contained

def day_04b(example: str) -> int:
    lines = example.splitlines()

    contained = 0
    for line in lines:
        left, right = [[int(i) for i in r.split("-")] for r in line.split(",")]
        if max(left[0], right[0]) <= min(left[1], right[1]):
            contained += 1

    return contained


