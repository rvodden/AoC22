#include <iostream>
#include <list>
#include <vector>

#include "lib.hpp"

namespace aoc {


void parse_inventory(
        std::vector<int64_t> &list,
        const std::string &inventory
) {
    std::stringstream stream(inventory);
    std::string line;
    while(std::getline(stream, line)) {
        list.push_back(std::stoi(line));
    }
}

std::ostream &operator<< (std::ostream &s, const std::pair<int, bool> &v) {
    s << "(" << v.first << "," << (v.second ? "true" : "false") << ")";
    return s;
}

std::ostream &operator<< (std::ostream &s, const std::list<std::pair<int64_t, bool>> &l) {
    for(const auto &[v, i] : l) {
        s << "(" << v << "," << i << ")";
    }
    return s;
}

std::list<std::pair<int64_t, std::size_t>>::iterator next_position(
    std::list<std::pair<int64_t,std::size_t>> &l,
    const std::size_t &i
) {
    return std::find_if( l.begin(), l.end(), [&i](auto &v){ return v.second == i; });
}

void step(
    std::list<std::pair<int64_t, std::size_t>> &working_list,
    const std::list<std::pair<int64_t, std::size_t>>::iterator &p,
    const int64_t list_size
) {
    if (p->first == 0) return;
    
    auto [value, index] = *p;
    int64_t distance = std::distance(working_list.begin(), p);
    int64_t travel = distance + value;
    int64_t new_position = travel % (list_size - 1);
    if (new_position <= 0)
        new_position += (list_size - 1);

    working_list.erase(p);
    auto new_position_pointer = working_list.begin();
    std::advance(new_position_pointer, new_position);
    working_list.emplace(new_position_pointer, std::make_pair(value, index));
}

void mix(std::list<std::pair<int64_t, std::size_t>> &working_list) {
    std::size_t list_size = working_list.size();

    for (std::size_t i = 0; i < list_size; i++) {
        auto p = next_position(working_list, i);
        step(working_list, p, list_size);
    }
}

int part_a(const std::string &inventory) {
    std::vector<int64_t> input_list;
    parse_inventory(input_list, inventory);

    std::size_t list_size = input_list.size();
    std::list<std::pair<int64_t, std::size_t>> working_list;

    std::size_t i = 0;
    for(auto v : input_list) {
        working_list.push_back({v, i++});
    }
    
    mix(working_list);

    auto first_zero = std::find_if(working_list.begin(), working_list.end(), [](const std::pair<int, int> &v){ return v.first == 0;});
    std::size_t distance_to_first_zero = std::distance(working_list.begin(), first_zero);
    
    std::vector<std::size_t> idxs = {
        (distance_to_first_zero + 1000) % list_size,
        (distance_to_first_zero + 2000) % list_size,
        (distance_to_first_zero + 3000) % list_size
    };


    int64_t result = 0;
    for (const auto &j : idxs){
        auto q = working_list.begin();
        std::advance(q, j);
        result += q->first;
    }
    return result;
}

void apply_encryption_key(
    const std::vector<int64_t> &input_list,
    std::list<std::pair<int64_t, std::size_t>> &working_list
) {
    const int64_t encryption_key = 811589153;
    
    std::size_t i = 0;
    for(auto v : input_list) {
        working_list.push_back({v * encryption_key, i++});
    }
}

int part_b(const std::string &inventory) {

    std::vector<int64_t> input_list;
    parse_inventory(input_list, inventory);

    std::size_t list_size = input_list.size();
    std::list<std::pair<int64_t, std::size_t>> working_list;

    apply_encryption_key(input_list, working_list);

    for(char k = 0; k< 10; k++){
        mix(working_list);
    }

    auto first_zero = std::find_if(working_list.begin(), working_list.end(), [](const std::pair<int, int> &v){ return v.first == 0;});
    std::size_t distance_to_first_zero = std::distance(working_list.begin(), first_zero);
    
    std::vector<std::size_t> idxs = {
        (distance_to_first_zero + 1000) % list_size,
        (distance_to_first_zero + 2000) % list_size,
        (distance_to_first_zero + 3000) % list_size
    };


    int64_t result = 0;
    for (const auto &j : idxs){
        auto q = working_list.begin();
        std::advance(q, j);
        result += q->first;
    }

    std::cout << result << std::endl;
    return result;
}

} // namespace aoc