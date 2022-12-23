#include <algorithm>
#include <regex>
#include <map>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>
#include <variant>

#include "day_7.hpp"

#define LENGTH_OF_MARKER 14

namespace aoc {


// a file is a size and a name
class File {
  public:
    std::string name;
    int size;

    inline File(std::string name_, int size_) : name(name_), size(size_) {};
};

// a directory is list of files, or other directories.
class Dir{
  public:
    std::string name;
    std::vector<File> files;
    std::vector<Dir> directories;

    // Would be interested to understand how to make this a reference;
    Dir* parent;
    int size;

    inline Dir(std::string name_): name(name_), parent(NULL), size(0) {};
    inline Dir(std::string name_, Dir& parent_): name(name_), parent(&parent_), size(0) {};

};

Dir* process_cd_command(const std::string &line, Dir &current_directory) {
    std::string name = line.substr(5);

    if (name == "/") return &current_directory; // this should return us to the root, but it only occurs at the top of the file.
    if (name == "..") return current_directory.parent; // in the real world we should be safer than this

    // given we're not at the root, find the directory with the specified name, and change to it
    for( Dir& d : current_directory.directories ) {
        if (name == d.name) return &d;
    }

    // we shouldn't get here, as we shouldn't try and change to a directory which doesn't exist
    return &current_directory;
}

void process_listing(const std::string &line, Dir &current_directory) {
    if (line.substr(0,3) == "dir") { 
        current_directory.directories.push_back(Dir(line.substr(4), current_directory));
        return;
    }

    auto pos = line.find(" ");
    int size = std::stoi(line.substr(0,pos));
    std::string name = line.substr(pos);
    current_directory.files.push_back(File(name, size));

    current_directory.size += size;
    Dir* cwd = current_directory.parent;
    while(cwd) {
        cwd->size += size;
        cwd = cwd->parent;
    }
}

Dir* process_line(const std::string &line, Dir &current_directory) {
    if (line[0] == '$') { // we're looking at a command
        std::string command = line.substr(2,2);
        if (command == "cd") { // we are changing to a directory
            return process_cd_command(line, current_directory);
        } else if (command == "ls") {
            return &current_directory; // nothing to do in this case 
        }
    }

    process_listing(line, current_directory);
    return &current_directory;
}

int sum_dir_size_below_limit(Dir dir, int limit) {
    int size = dir.size <= limit ? dir.size : 0;
    for (auto sdir : dir.directories) size += sum_dir_size_below_limit(sdir, limit);
    return size; 
}

int day_7a(const std::string &inventory) {
    std::stringstream stream(inventory);
    std::string line;

    Dir root("/");

    Dir *working_directory = &root;

    while(std::getline(stream, line)) {
        working_directory = process_line(line, *working_directory);
    }

    return sum_dir_size_below_limit(root, 100000);
}

std::optional<int> find_smallest_dir_above_target(Dir dir, int target) {
    if (dir.size < target) return std::nullopt;

    int size = dir.size;
    std::optional<int> ssize;
    for( auto sdir : dir.directories ) {
        ssize = find_smallest_dir_above_target(sdir, target);
        if (ssize == std::nullopt || ssize.value() < target) continue;
        size = ssize.value() < size ? ssize.value() : size;
    }

    return size;
}

int day_7b(const std::string &inventory) {
    std::stringstream stream(inventory);
    std::string line;

    Dir root("/");

    Dir *working_directory = &root;

    while(std::getline(stream, line)) {
        working_directory = process_line(line, *working_directory);
    }

    int target = 30000000 - (70000000 - root.size);
    return find_smallest_dir_above_target(root, target).value();
}
} // namespace aoc