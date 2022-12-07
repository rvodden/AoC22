def location_of_first_unique_consecutive_substring(length: int, string: str):
    return next(((i + length) for i in range(len(string) - length-1) if len(set(string[i:i+length])) == length))

def day_06a(example: str):
    return location_of_first_unique_consecutive_substring(4, example)

def day_06b(example: str):
    return location_of_first_unique_consecutive_substring(14, example)