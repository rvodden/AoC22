#include <algorithm>
#include <functional>
#include <optional>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

#include "day13.hpp"

namespace aoc {

std::optional<bool> _correct_order(const List &first, const List &second) {
    if (std::holds_alternative<int>(first) and std::holds_alternative<int>(second)) {
        int a = std::get<int>(first);
        int b = std::get<int>(second);

        if (a == b) return std::nullopt;

        return (std::get<int>(first) < std::get<int>(second));
    }

    if (std::holds_alternative<std::vector<List>>(first) and std::holds_alternative<int>(second))
        return _correct_order(first, std::vector<List>{std::get<int>(second)});

    if (std::holds_alternative<int>(first) and std::holds_alternative<std::vector<List>>(second))
        return _correct_order(std::vector<List>{std::get<int>(first)}, second);

    auto f = std::get<std::vector<List>>(first);
    auto s = std::get<std::vector<List>>(second);

    auto fi = f.begin();
    auto si = s.begin();

    while( fi != f.end() and si != s.end() ) {
        std::optional<bool> comp = _correct_order(*fi, *si);
        if ( comp.has_value() ) return comp;
        fi++; si++;
    }

    if (fi == f.end() and si == s.end()) return std::nullopt;

    return fi == f.end();
}

bool correct_order(const List &first, const List &second) {
    return _correct_order(first, second).value();
}

List parse_list(std::string::iterator start, std::string::iterator end) {
    std::vector<List> l;
    for (auto i = start; i < end; i++) {
        if (*i == '[') {
            auto loc = std::find(i, end, ']');
            l.push_back(parse_list(i+1, loc));
            i = loc + 1;
            continue;
        };

        if (*i == ',' || *i == ']') continue;

        auto loc = std::find(i, end, ',');
        auto s = std::string(i, loc);
        // std::cout << s << std::endl;
        l.push_back(std::stoi(s));
        i = loc;
    }
    return l;
}

List parse_list(std::string str) {
    return parse_list(str.begin() + 1, str.end() - 1);
}

int part_a(const std::string &inventory) {
    std::stringstream stream(inventory);
    int i = 0; int total = 0;

    std::string a;
    std::string b;
    std::string c;
    while(stream) {
        i++;
        std::getline(stream, a);
        std::getline(stream, b);
        std::getline(stream, c); // blank line

        List l = parse_list(a);
        List m = parse_list(b);

        if (correct_order(l, m)) total += i;
    }

    return total;
}

int part_b(const std::string &inventory) {
    std::stringstream stream(inventory);
    std::vector<List> lists;

    std::string a;
    std::string b;
    std::string c;

    List l;
    List m;

    while(stream) {
        std::getline(stream, a);
        std::getline(stream, b);
        std::getline(stream, c); // blank line

        l = parse_list(a);
        m = parse_list(b);

        lists.push_back(l);
        lists.push_back(m);
    }

    using V = std::vector<List>;

    List d1 = V{V{2}};
    List d2 = V{V{6}};

    lists.push_back(d1);
    lists.push_back(d2);

    std::sort(lists.begin(), lists.end(), correct_order);

    auto loc_d1 = std::find(lists.begin(), lists.end(), d1);
    auto loc_d2 = std::find(lists.begin(), lists.end(), d2);

    return ( std::distance(lists.begin(), loc_d1) + 1 ) * ( std::distance(lists.begin(), loc_d2) + 1 );
}

} // namespace aoc