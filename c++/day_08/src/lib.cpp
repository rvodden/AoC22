#include <algorithm>
#include <array>
#include <regex>
#include <map>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>
#include <variant>

#include "lib.hpp"

namespace aoc {

/**
 * Load the tree heights into a one dimensional vector, and return the dimensions.
 * 
 * Using a 1-d vector means that we can use arithmetic to navigate around the two dimensions.
*/
std::pair<int, int> parse_heights(const std::string &inventory, std::vector<char> &field_of_trees) {

    std::stringstream stream(inventory);
    std::string line;

    int depth = 0;
    int breadth;
    while( std::getline(stream, line) ) {
        breadth = 0;
        for (const auto &c : line) {
            field_of_trees.push_back(c - 48);
            breadth++;
        }
        depth++;
    }

    return std::pair<int,int>(breadth, depth);
}

void look_in_from_left(const std::pair<int,int> &dimensions, const std::vector<char> &field_of_trees, std::vector<bool> &field_of_visibility) {
    const auto& [breadth, depth] = dimensions;

    // look in from the left
    auto row = field_of_trees.begin();
    auto row_visibility = field_of_visibility.begin();
    while(row < field_of_trees.end()) {
        auto tree = row; // copy the row iterators
        auto tree_visibility = row_visibility;

        // first column is always visible
        *tree_visibility = true;
        int tallest_tree =  *tree;
        tree++; tree_visibility++;

        while( tree - row < breadth ) {
            if( *tree > tallest_tree ) {
                tallest_tree = *tree;
                *tree_visibility = true;
            }
            tree++; tree_visibility++;
        }

        row += breadth;
        row_visibility += breadth;
    }
}

void look_in_from_right(const std::pair<int,int> &dimensions, const std::vector<char> &field_of_trees, std::vector<bool> &field_of_visibility) {
    const auto& [breadth, depth] = dimensions;

    // look in from the left
    auto row = field_of_trees.rbegin();
    auto row_visibility = field_of_visibility.rbegin();
    while(row < field_of_trees.rend()) {
        auto tree = row; // copy the row iterators
        auto tree_visibility = row_visibility;

        // first column is always visible
        *tree_visibility = true;
        int tallest_tree =  *tree;
        tree++; tree_visibility++;

        while( tree - row < breadth ) {
            if( *tree > tallest_tree ) {
                tallest_tree = *tree;
                *tree_visibility = true;
            }
            tree++; tree_visibility++;
        }

        row += breadth;
        row_visibility += breadth;
    }
}

void look_in_from_top(const std::pair<int,int> &dimensions, const std::vector<char> &field_of_trees, std::vector<bool> &field_of_visibility) {
    const auto& [breadth, depth] = dimensions;

    // look in from the left
    auto column = field_of_trees.begin();
    auto column_visibility = field_of_visibility.begin();
    while(column - field_of_trees.begin() < breadth) {
        auto tree = column; // copy the row iterators
        auto tree_visibility = column_visibility;

        // first column is always visible
        *tree_visibility = true;
        int tallest_tree =  *tree;
        tree += breadth; tree_visibility += breadth;

        while( tree < field_of_trees.end() ) {
            if( *tree > tallest_tree ) {
                tallest_tree = *tree;
                *tree_visibility = true;
            }
            tree += breadth; tree_visibility += breadth;
        }

        column++;
        column_visibility++;
    }
}

void look_in_from_bottom(const std::pair<int,int> &dimensions, const std::vector<char> &field_of_trees, std::vector<bool> &field_of_visibility) {
    const auto& [breadth, depth] = dimensions;

    // look in from the left
    auto column = field_of_trees.rbegin();
    auto column_visibility = field_of_visibility.rbegin();
    while(column - field_of_trees.rbegin() < breadth) {
        auto tree = column; // copy the row iterators
        auto tree_visibility = column_visibility;

        // first column is always visible
        *tree_visibility = true;
        int tallest_tree = *tree;
        tree += breadth; tree_visibility += breadth;

        while( tree < field_of_trees.rend() ) {
            if( *tree > tallest_tree ) {
                tallest_tree = *tree;
                *tree_visibility = true;
            }
            tree += breadth; tree_visibility += breadth;
        }

        column++;
        column_visibility++;
    }
}

int part_a(const std::string &inventory) {
    std::vector<char> field_of_trees;
    const auto dimensions = parse_heights(inventory, field_of_trees);
    const auto [depth, breadth] = dimensions;

    std::vector<bool> field_of_visiblity(depth * breadth, false);

    look_in_from_left(dimensions, field_of_trees, field_of_visiblity);
    look_in_from_right(dimensions, field_of_trees, field_of_visiblity);
    look_in_from_top(dimensions, field_of_trees, field_of_visiblity);
    look_in_from_bottom(dimensions, field_of_trees, field_of_visiblity);

    auto count = std::count(field_of_visiblity.begin(), field_of_visiblity.end(), true);

    return count;
}

std::pair<int, int> dimensions(const int &value, const int &breadth) {
    auto [y, x] = std::div(value, breadth);
    return std::make_pair(x, y);
}

bool edge_of_the_world(const int &increment, const int &breadth, const int &depth, const int &x, const int &y) {
    return ( (increment == 1 and x == (breadth - 1)) or
         (increment == -1 and x == 0 ) or
         (increment > 1 and y == (depth - 1)) or
         (increment < -1 and y == 0 ));
}

template<typename T1, typename T2> //needs to cope with iterator and reverse_iterator
int visibility(
        const T1 &start_visibility, 
        const T2 &start_tree, 
        const T2 &end_tree, 
        const signed char increment){
    auto v = start_visibility;

    // if we already know the answer, then just return it
    if (v->has_value() ) return v->value();

    auto t = start_tree;
    auto nt = t + increment;
    int distance = 1;

    while ( *nt < *t and nt < end_tree ) { // the trees are shorter
        distance++;
        nt += increment;
    }

    *v = distance;
    return v->value();
}

int part_b(const std::string &inventory) {
    std::vector<char> trees;
    const auto dimensions = parse_heights(inventory, trees);
    const auto [depth, breadth] = dimensions;

    std::array<std::vector<std::optional<int>>,4> visibilities;
    visibilities.fill(std::vector(depth * breadth, std::optional<int>(), std::allocator<std::optional<int>>()));

    const auto [NORTH, EAST, SOUTH, WEST] = std::make_tuple(0, 1, 2, 3);
    const auto [NORTH_INC, EAST_INC, SOUTH_INC, WEST_INC] = std::make_tuple(-breadth, 1, breadth, -1);

    
    auto tree = trees.begin();
    auto vs = visibilities[SOUTH].begin();
    auto ve = visibilities[EAST].begin();
    auto eowt = trees.begin() + breadth - 1;
    for (int i = 0; i < depth; i++ ) {
        auto sreowt = trees.end() - breadth;
        for (int j = 0; j < breadth; j++) {
            if ( i == depth - 1 )
                *vs = 0;
            if ( j == breadth - 1 )
                *ve = 0;   
            visibility(vs, tree, sreowt, SOUTH_INC);
            visibility(ve, tree, eowt, EAST_INC);
            tree++; vs++; ve++; sreowt++;
        }
        eowt += breadth;
    }

    auto rtree = trees.rbegin();
    auto vn = visibilities[NORTH].rbegin();
    auto vw = visibilities[WEST].rbegin();
    auto reowt = trees.rbegin() + breadth - 1;
    for (int i = 0; i < depth; i++ ) {
        auto nreowt = trees.rend() - breadth;
        for (int j = 0; j < breadth; j++) {
            if ( i == depth - 1 )
                *vn = 0;
            if ( j == breadth - 1 )
                *vw = 0;   
            visibility(vn, rtree, nreowt, -NORTH_INC);
            visibility(vw, rtree, reowt, -WEST_INC);
            rtree++; vn++; vw++; nreowt++;
        }
        reowt += breadth;
    }

    int max = 0;
    auto n = visibilities[NORTH].begin();
    auto e = visibilities[EAST].begin();
    auto s = visibilities[SOUTH].begin();
    auto w = visibilities[WEST].begin();

    while (n != visibilities[NORTH].end()) {
        int v = n->value() * e->value() * s->value() * w->value();
        max = std::max(max, v);       
        n++; e++; s++; w++;
    }

    return max;
}

} // namespace aoc