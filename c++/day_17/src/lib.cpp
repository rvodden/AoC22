#include <bitset>
#include <deque>
#include <iostream>
#include <numeric>
#include <vector>

#include "lib.hpp"

namespace aoc {


void parse_inventory(std::vector<char> &directions, const std::string &inventory) {
    directions = std::vector<char>(inventory.begin(), inventory.end());
}

const std::vector<std::vector<std::bitset<7>>> rocks = {
    {
        0b0011110
    },{
        0b0001000,
        0b0011100,
        0b0001000
    },{
        0b0000100,
        0b0000100,
        0b0011100
    },{
        0b0010000,
        0b0010000,
        0b0010000,
        0b0010000
    },{
        0b0011000,
        0b0011000
    }
};


void Chamber::process_direction(
    std::vector<std::bitset<7>> &rock_rows,
    const std::vector<std::deque<std::bitset<7>>::iterator> &sliding_window 
) {
    const char &c = _direction_provider.next();
    switch (c)
    {
        case '<':
            left(rock_rows, sliding_window);
            log("Left!");
            break;
        
        case '>':
            right(rock_rows, sliding_window);
            log("Right");
            break;
        default:
            log("This should never happen!");
            std::cout << (int)c << std::endl;
    }
}

void Chamber::left (
    std::vector<std::bitset<7>> &vector,
    const std::vector<std::deque<std::bitset<7>>::iterator> &sliding_window 
) {
    const auto backup = vector;
    for( const auto &row : vector ) {
        if (row.test(6)) {
            return;
            _previous_direction = 0;
        }
    }
    for(auto &row : vector) {
        row <<= 1;
    }
    if(clash(vector, sliding_window)) vector = backup;
} 

void Chamber::right (std::vector<std::bitset<7>> &vector,
    const std::vector<std::deque<std::bitset<7>>::iterator> &sliding_window
) {
    const auto backup = vector;
    for( const auto &row : vector ) {
        if (row.test(0)) {
            return;
            _previous_direction = 0;
        }
    }
    _previous_direction = '>';
    for( auto &row : vector ) {
        row >>= 1; 
    }
    if(clash(vector, sliding_window)) vector = backup;
} 

bool Chamber::clash(
    const std::vector<std::bitset<7>> &rock_rows,
    const std::vector<std::deque<std::bitset<7>>::iterator> &sliding_window
) const {
    auto s = sliding_window.begin();
    auto nr = rock_rows.begin();
    
    while( s < sliding_window.end() ) {
        if ( (**s & *nr).any() ) 
            return true;
        s++; nr++;
    }

    return false;
}

bool Chamber::descent_would_block(
    const std::vector<std::bitset<7>> &rock_rows,
    std::vector<std::deque<std::bitset<7>>::iterator> sliding_window
) const {
    for(auto &t : sliding_window) {
        t++;
    }
    return clash(rock_rows, sliding_window);
}

void Chamber::down ( 
    std::vector<std::deque<std::bitset<7>>::iterator> &sliding_window
) const
{
    for(auto &t : sliding_window) {
        t++;
    }
}

void Chamber::add_rock(const std::vector<std::bitset<7>> &rock) {
    std::vector<std::bitset<7>> rock_rows = rock;
    ensure_n_clear_rows(3 + rock_rows.size());

    std::vector<std::deque<std::bitset<7>>::iterator> sliding_window;
    log("New Rock!");
    auto start = _chamber.begin();
    for ( size_t i = 0; i < rock_rows.size(); i++ ) {
        sliding_window.push_back(start++);
    }
    
    while(sliding_window.back() != _chamber.end()) {        
        print(rock_rows, sliding_window.front());
        process_direction(rock_rows, sliding_window);
        print(rock_rows, sliding_window.front());
        if(descent_would_block(rock_rows, sliding_window)) break;
        log("Down!");
        down(sliding_window);
    }

    auto s = sliding_window.begin();
    auto nr = rock_rows.begin();

    while( s < sliding_window.end() ) {
        **s = *nr | **s;
        s++; nr++;
    }

    print(rock_rows, sliding_window.front());
}

void Chamber::print() const {
    if(!_print_enabled) return;
    for(auto i = _chamber.begin(); i < _chamber.end(); i++ ) {
        for(int j = 6; j >= 0; j-- ) {
            std::cout << (i->test(j) ? "#" : ".");
        }
        std::cout << std::endl;
    }
}

void Chamber::print(const std::vector<std::bitset<7>> &rock, const std::deque<std::bitset<7>>::iterator &pos ) const { 
    if(!_print_enabled) return;
    bool print_rock = false;
    auto rock_row = rock.begin();
    for(auto i = _chamber.begin(); i < _chamber.end(); i++ ) {
        if (i == pos) print_rock = true;

        for(int j = 6; j >= 0; j-- ) {
            char c = '.';
            if ( i->test(j) ) c = '#';
            if ( print_rock && rock_row->test(j) ) c = '@';
            std::cout << c;
        }

        if ( print_rock ) {
            rock_row++;
            print_rock = (rock_row != rock.end());
        }
        std::cout << std::endl;
    }

}

std::vector<std::bitset<7>> Chamber::rock_to_rows(const Rock &rock) const {
    std::vector<std::bitset<7>> rows;
    for(auto &rock_row : rock) {
        int bit = 2;
        std::bitset<7> row(0);
        for( const auto &rock_cell : rock_row ) {
            if(rock_cell) row.set(bit);
            bit++;
        }
        rows.push_back(row);
    }
    return rows;
}

void Chamber::ensure_n_clear_rows(std::size_t n) {
    std::size_t count = 0;
    for(const auto &row : _chamber ) {
        if(row.any()) break;
        count++;
    }

    if( n > count ) {
        for(std::size_t i = 0; i < (n - count); i++) {
            add_row();
        }
        return;
    }

    for(std::size_t i = 0; i < (count- n); i++) {
        _chamber.pop_front();
    }

}

void Chamber::clean() {
    while(_chamber.front().none()) {
        _chamber.pop_front();
    }
}

uint64_t Chamber::hash() const {
    uint64_t byte1 = 0;
    uint64_t byte2 = 0;
    const int length = 64 / 7;

    auto curr = _chamber.cbegin();
    for(int i = 0; i < length; i++ ) {
        if (curr == _chamber.cend()) break;
        byte1 <<= length;
        byte1 += curr->to_ulong();
        curr++;
    }

    for(int i = 0; i < length; i++ ) {
        if (curr == _chamber.cend()) break;
        byte2 <<= length;
        byte2 += curr->to_ulong();
        curr++;
    }
    
    return byte1 ^ (1035301 * byte2) ^ (1062601 *_direction_provider.state());
}

int64_t part_a(const std::string &inventory) {
    std::vector<char> directions;
    parse_inventory(directions, inventory);

    Cycler<std::vector, char> dp(directions);
    Cycler<std::vector, std::vector<std::bitset<7>>> rock_provider(rocks);
    Chamber chamber(dp);

    for(int i = 0; i < 2022; i++) {
        chamber.add_rock(rock_provider.next());
        // chamber.print();
    }

    chamber.clean();

    return chamber.size() - 1;
}

uint64_t part_b(const std::string &inventory) {
    std::vector<char> directions;
    parse_inventory(directions, inventory);

    Cycler<std::vector, char> dp(directions);
    Cycler<std::vector, std::vector<std::bitset<7>>> rock_provider(rocks);
    Chamber chamber(dp);

    uint64_t hash;
    uint64_t idx = 0;
    std::unordered_map<uint64_t, std::pair<uint64_t, uint64_t>> hash_table;
    while(true) {
        chamber.add_rock(rock_provider.next());
        hash = chamber.hash() ^ (1003001 * rock_provider.state());
        if(hash_table.contains(hash)) break;
        chamber.clean();
        hash_table[hash] = {idx, chamber.size()};
        idx++;
    }
    
    chamber.clean();
    std::cout << "Loops at : " << idx << " back to " << hash_table.at(hash).first << std::endl;
    std::cout << "The tower is now " << chamber.size() << std::endl;
    std::cout << "and was " << hash_table.at(hash).second << std::endl;
    std::cout << "the process therefore loops every " << idx - hash_table.at(hash).first << " rocks" << std::endl;
    std::cout << "during which the tower grows " << chamber.size() - hash_table.at(hash).second << std::endl;

    std::cout << "The initial offset is, therefore, " << hash_table.at(hash).first << "." << std::endl;
    
    uint64_t rock_count = 1000000000000LL - hash_table.at(hash).first;
    uint64_t loop_length = idx - hash_table.at(hash).first;
    uint64_t number_of_loops = rock_count/loop_length;
    uint64_t loop_remainder = rock_count % loop_length;
    uint64_t loop_tower_growth = chamber.size() - hash_table.at(hash).second;

    std::cout << "So we need to work out the growth from " << 1000000000000LL - hash_table.at(hash).first << std::endl;
    std::cout << "There will be " << number_of_loops << " loops" << std::endl;
    std::cout << "With " << loop_remainder << " left over" << std::endl;

    uint64_t simulation_length = loop_remainder + hash_table.at(hash).first;

    std::cout << "So run the simulation with " << simulation_length << std::endl;

    chamber.clear();
    rock_provider.reset();

    for(uint64_t i = 0; i < simulation_length; i++) {
        chamber.add_rock(rock_provider.next());
    }

    std::cout << "The chamber is now " << chamber.size() << " high" << std::endl;

    uint64_t chamber_height = number_of_loops * loop_tower_growth + chamber.size();  // minus two takes into account the floor
    
    std::cout << "So the answer (possibly) is " << chamber_height << std::endl;

    return chamber_height;
}

} // namespace aoc