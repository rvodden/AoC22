from typing import Optional

class Directory:
    size: int
    parent: "Directory"
    directories: dict[str, "Directory"]
    files: dict[str, int]

    def __init__(self, parent: Optional["Directory"] = None):
        self.parent = parent

        self.size = 0
        self.directories = {}
        self.files = {}

    def add_file(self, name, size):
        self.files[name] = size
        self.size += size
        
        parent = self.parent
        while( parent ):
            parent.size += size
            parent = parent.parent


def parse_instructions(example:str) -> Directory:
    lines = example.splitlines()

    filesystem = Directory()

    cwd = filesystem

    for line in lines:
        match line.split():
            case ["$", "ls"]:
                pass # nothing to do here
            case ["$", "cd", "/"]:
                cwd = filesystem
            case ["$", "cd", ".."]:
                cwd = cwd.parent
            case ["$", "cd", name]:
                cwd = cwd.directories[name]
            case ["dir", name]:
                cwd.directories[name] = Directory(cwd)
            case [size, name]:
                cwd.add_file(name, int(size))
            case _:
                print("I have failed in life");
                exit(-1);
    return filesystem


def sum_directories_less_than_limit(dir: Directory, limit: int):
    total = dir.size if dir.size <= limit else 0
    for _, sdir in dir.directories.items():
        total += sum_directories_less_than_limit(sdir, limit)
    return total


def day07a(example: str) -> int:
    filesystem = parse_instructions(example)
    return sum_directories_less_than_limit(filesystem, 100000)

def find_smallest_size_above_target(directory: Directory, target: int) -> int:
    if directory.size < target:
        return None
    size = directory.size
    for _, sdir in directory.directories.items():
        ssize = find_smallest_size_above_target(sdir, target)
        if ssize:
            size = ssize if not size else min(size, ssize)
    return size

def day07b(example: str) -> int:
    filesystem = parse_instructions(example)
    target = 30000000 - (70000000 - filesystem.size)
    return find_smallest_size_above_target(filesystem, target)
