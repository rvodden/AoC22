def day_02a(example: str) -> int:
    scores = { "A X": 1 + 3,  # rock + rock
               "A Y": 2 + 6,  # rock + paper
               "A Z": 3 + 0,  # rock + scissors
               "B X": 1 + 0,  # paper + rock
               "B Y": 2 + 3,  # paper + paper
               "B Z": 3 + 6,  # paper + scissors
               "C X": 1 + 6,  # scissors + rock
               "C Y": 2 + 0,  # scissors + paper
               "C Z": 3 + 3   # scissors + scissors
    }
    return sum(scores[line] for line in example.splitlines())

def day_02b(example: str) -> int:
    scores = { "A X": 0 + 3, # rock + lose (play scissors)
               "A Y": 3 + 1, # rock + draw (play rock)
               "A Z": 6 + 2, # rock + win (play paper)
               "B X": 0 + 1, # paper + lose (play rock)
               "B Y": 3 + 2, # paper + draw (play paper)
               "B Z": 6 + 3, # paper + win (play scissors)
               "C X": 0 + 2, # scissors + lose (play paper)
               "C Y": 3 + 3, # scissors + draw (play scissors)
               "C Z": 6 + 1 # scissors + win (play rock)
    }
    return sum(scores[line] for line in example.splitlines())