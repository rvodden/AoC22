#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include "lib.hpp"

namespace aoc {

Snafu parse_snafu(const std::string &input) {
    Snafu snafu;
    for (const auto &c : input) {
        switch(c) {
          case '2':
            snafu.push(2);
            break;
          case '1':
            snafu.push(1);
            break;
          case '0':
            snafu.push(0);
            break;
          case '-':
            snafu.push(-1);
            break;
          case '=':
            snafu.push(-2);
            break;
          default:
            std::cout << (int) c << std::endl;
            throw std::runtime_error("Invalid character.");
        }
    }
    return snafu;
}

void parse_input(std::vector<Snafu> &snafus, const std::string &input) {
    std::stringstream stream(input);
    std::string line;
    while(std::getline(stream, line)) {
        snafus.push_back(parse_snafu(line));
    }
}

int64_t snafu_to_int(const Snafu &input) {
    int64_t result = 0;
    int64_t factor = 1;
    Snafu local_snafu = input;
    while(! local_snafu.empty() ) {
        result += factor * local_snafu.top();
        local_snafu.pop();
        if( factor * 5 < factor)
            throw std::runtime_error("Overflow!");
        factor *= 5;
    }
    return result;
}

std::string snafu_to_string(const Snafu &input) {
    std::stringstream s;
    Snafu local_snafu = input;
    while(!local_snafu.empty()) {
        auto t = local_snafu.top();
        local_snafu.pop();
        switch(t) {
            case 2:
                s << "2";
                break;
            case 1:
                s << "1";
                break;
            case 0:
                s << "0";
                break;
            case -1:
                s << "-";
                break;
            case -2:
                s << "=";
                break;
          default:
            std::cout << t << std::endl;
            throw std::runtime_error("Invalid value.");
        }
    }
    std::string temp = s.str();
    // flip the string around cause I'm dumb
    return std::string(temp.rbegin(), temp.rend());
}

int64_t snafu_to_int(const std::string &input){
    return snafu_to_int(parse_snafu(input));
}

Snafu int_to_snafu(const int64_t& target) {
    int64_t local_target = target;
    std::deque<int8_t> proto_snafu;
    while(local_target > 0) {
        int64_t digit = local_target % 5;
        local_target /= 5;
        switch(digit) {
            case 0:
                proto_snafu.push_front(0);
                break;
            case 1:
                proto_snafu.push_front(1);
                break;
            case 2:
                proto_snafu.push_front(2);
                break;
            case 3:
                proto_snafu.push_front(-2);
                local_target ++;
                break;
            case 4:
                proto_snafu.push_front(-1);
                local_target ++;
                break;
            default:
                std::cout << (int) digit << std::endl;
                throw std::runtime_error("Invalid character.");
        }
    }
    return Snafu(proto_snafu);
};

std::string int_to_snafu_string(const int64_t &target) {
    Snafu snafu = int_to_snafu(target);
    return snafu_to_string(snafu);
}

std::string part_a(const std::string &input) {
    std::vector<Snafu> snafus;
    parse_input(snafus, input);
    std::vector<int64_t> results(snafus.size());
    std::ranges::transform(snafus.begin(), snafus.end(), results.begin(), 
      [](const auto &s) { return snafu_to_int(s); });

    int64_t result = std::accumulate(results.begin(), results.end(), 0LL);

    std::cout << result << std::endl;
    return int_to_snafu_string(result);
}

int part_b(const std::string &input) {
    return -1;
}

} // namespace aoc