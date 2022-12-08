#include <algorithm>
#include <regex>
#include <map>
#include <iostream>
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

int visibility(
        const std::vector<char> &trees, 
        std::vector<std::optional<int>> &visibilities, 
        const int &breadth, const int &depth, 
        const std::vector<char>::iterator &tree, 
        const signed char increment){
    auto t = tree;
    auto idx = t - trees.begin();
    auto v = visibilities.begin() + idx;

    // if we already know the answer, then just return it
    if (v->has_value() ) return v->value();

    auto [x, y] = dimensions(idx, breadth);
    if ( edge_of_the_world(increment, breadth, depth, x, y) ) {
        // we're looking off the edge of the world
        *v = 0;
        return 0;
    } 
    
    auto nt = t + increment;
    idx += increment;
    int distance = 1;

    auto dim = dimensions(idx, breadth);
    x = dim.first; y = dim.second;
    while ( *nt < *t and not edge_of_the_world(increment, breadth, depth, x, y)) { // the trees are shorter
        distance++;
        nt += increment;
        idx += increment;
        dim = dimensions(idx, breadth);
        x = dim.first; y = dim.second;
    }
    *v = distance;
    return v->value();
    
    // one more that the value that neighbour has in that direction
    *v = 1 + visibility(trees, visibilities, breadth, depth, nt, increment);
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


    int idx = 0;
    auto tree = trees.begin();
    while ( tree != trees.end() ) {
        visibility(trees, visibilities[NORTH], breadth, depth, tree, NORTH_INC);
        visibility(trees, visibilities[EAST], breadth, depth, tree, EAST_INC);
        visibility(trees, visibilities[SOUTH], breadth, depth, tree, SOUTH_INC);
        visibility(trees, visibilities[WEST], breadth, depth, tree, WEST_INC);
        idx++; tree++;
    }

    int max = 0;
    auto n = visibilities[NORTH].begin();
    auto e = visibilities[EAST].begin();
    auto s = visibilities[SOUTH].begin();
    auto w = visibilities[WEST].begin();

    while (n != visibilities[NORTH].end()) {
        int v = n->value() * e->value() * s->value() * w->value();
        // std::cout << v << std::endl;
        max = std::max(max, v);       
        n++; e++; s++; w++;
    }

    for (int d : {
        NORTH, 
        EAST, 
        SOUTH, 
        WEST
        }) {
        auto v = visibilities[d].begin();
        for (int i = 0; i < depth; i++) {
            for (int j = 0; j < breadth; j++  ) {
                if (v->has_value()) 
                    std::cout << v->value(); 
                else 
                    std::cout << '-';
                v++;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    return max;
}

} // namespace aoc