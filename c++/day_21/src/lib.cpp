#include <iostream>
#include <list>
#include <regex>
#include <sstream>
#include <vector>
#include <variant>

#include "lib.hpp"

namespace aoc {

enum class Operator {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE
};

std::ostream& operator<<(std::ostream& stream, const Operator &o) {
    std::string s;
    switch(o) {
        case Operator::ADD:
            s = "+";
            break;
        case Operator::MULTIPLY:
            s = "*";
            break;
        case Operator::DIVIDE:
            s = "/";
            break;
        case Operator::SUBTRACT:
            s = "-";
            break;
    }
    stream << s;
    return stream;
}

using Monkey = std::string;
using Expression = std::pair<Operator, std::pair<Monkey, Monkey>>;
using Line = std::variant<int64_t, Expression>;
using Riddle = std::unordered_map<Monkey, Line>;

// helper struct for overload pattern
template<typename ... Ts> 
struct Overload : Ts ... { 
    using Ts::operator() ...; 
};
// deduction guide
template<class... Ts> Overload(Ts...) -> Overload<Ts...>;

std::ostream& operator<< (std::ostream& s, const Expression &e) {
    s << e.second.first << " " << e.first << " " << e.second.second;
    return s;
}

std::ostream& operator<<(std::ostream& s, const Line &l) {
    auto TypeOfLine = Overload {
       [&s](const int64_t &i) { s << i; },
       [&s](const Expression &e) { s << e; }
    }; 

    std::visit(TypeOfLine, l);
    return s;
}

void parse_input(
        std::unordered_map<std::string, Line> &riddle,
        const std::string &input
) {
    std::regex regex(R"R((\w{4}): (?:(\d+)|(?:(\w{4}) ([+-/*]) (\w{4}))))R",std::regex_constants::ECMAScript);
    
    std::stringstream stream(input);
    std::string input_line;
    std::smatch matches;
    while(std::getline(stream, input_line)) {
        if (! std::regex_match(input_line, matches, regex) ) {
            std::cout << input_line << std::endl;
            throw std::runtime_error("Regex didn't match");
        }

        std::string monkey = matches[1];

        try {    
            riddle[monkey] = Line(std::stoi(matches[2]));
            continue;
        } catch (std::invalid_argument const& e) { }

        Operator o;
        switch(*matches[4].first) {
          case '+':
            o = Operator::ADD;
            break;
          case '-':
            o = Operator::SUBTRACT;
            break;
          case '/':
            o = Operator::DIVIDE;
            break;
          case '*':
            o = Operator::MULTIPLY;
            break;
          default:
            break;
        }

        riddle[monkey] = Line(std::make_pair(o, std::make_pair(matches[3].str(), matches[5].str())));
    }
}

std::function<int64_t(const int64_t&, const int64_t&)> get_operator(const Operator &o) {
    switch(o) {
        case Operator::ADD:
            return [](const auto& l,const auto &r) { return l + r; };
        case Operator::SUBTRACT:
            return [](const auto& l,const auto &r) { return l - r; };
        case Operator::MULTIPLY:
            return [](const auto& l,const auto &r) { return l * r; };
        case Operator::DIVIDE:
            return [](const auto& l,const auto &r) { return l / r; };
        default:
            throw std::runtime_error("Cannot match exception");
    }
}

// x = a - y => y = a - x
// x = a + y => y = x - a
// x = a / y => y = a / x
// x = a * y => y = x / y

std::function<int64_t(const int64_t&, const int64_t&)> get_lhs_inverse_operator(const Operator &o) {
    switch(o) {
        case Operator::ADD:
            return [](const auto& l,const auto &r) { return l - r; };
        case Operator::SUBTRACT:
            return [](const auto& l,const auto &r) { return r - l; };
        case Operator::MULTIPLY:
            return [](const auto& l,const auto &r) { return l / r; };
        case Operator::DIVIDE:
            return [](const auto& l,const auto &r) { return r / l; };
        default:
            throw std::runtime_error("Cannot match exception");
    }
}

std::function<int64_t(const int64_t&, const int64_t&)> get_rhs_inverse_operator(const Operator &o) {
    switch(o) {
        case Operator::ADD:
            return [](const auto& l,const auto &r) { return l - r; };
        case Operator::SUBTRACT:
            return [](const auto& l,const auto &r) { return l + r; };
        case Operator::MULTIPLY:
            return [](const auto& l,const auto &r) { return l / r; };
        case Operator::DIVIDE:
            return [](const auto& l,const auto &r) { return l * r; };
        default:
            throw std::runtime_error("Cannot match exception");
    }
}

int64_t evaluate(const std::unordered_map<std::string, Line> &riddle, const Line &l) {
    auto TypeOfLine = Overload {
       [](const int64_t &i) { 
            return i; 
        },
       [&riddle](const std::pair<Operator,std::pair<std::string, std::string>> &e) { 
            return get_operator(e.first)(
                evaluate(riddle, riddle.at(e.second.first)), 
                evaluate(riddle, riddle.at(e.second.second))
            );
        }
    }; 
    int64_t result = std::visit(TypeOfLine, l);
    return result;
}

int part_a(const std::string &input) {
    Riddle riddle;
    parse_input(riddle, input);

    int64_t result = evaluate(riddle, riddle["root"]);
    std::cout << result << std::endl;
    return result;
}

bool requires_monkey(const Riddle &riddle, const Monkey &starting_monkey, const Monkey &required) {
    if(std::holds_alternative<int64_t>(riddle.at(starting_monkey))) return false;

    const Expression &expression = std::get<Expression>(riddle.at(starting_monkey));
    const auto &[_, monkeys] = expression;

    if(monkeys.first == required || monkeys.second == required) return true;

    return requires_monkey(riddle, monkeys.first, required) || requires_monkey(riddle, monkeys.second, required);
}


int64_t solve(const Riddle &riddle, const Monkey &starting_monkey, int64_t target) {
    const Expression &expression = std::get<Expression>(riddle.at(starting_monkey)); 
    auto &[opp, monkeys] = expression;
    auto &[monkey1, monkey2] = monkeys;

    // std::cout << expression << " = " << target << std::endl;

    Monkey dependent;
    int64_t other;
    
    if (monkey1 == "humn") {
        // target = humn op other
        // humn = target invop other
        other = evaluate(riddle, riddle.at(monkey2));
        // std::cout << monkey1 << " = " << other << std::endl;
        return get_rhs_inverse_operator(opp)(target, other);
    }

    if (monkey2 == "humn"){
        // target = other op humn
        // humn = other invop target
        other = evaluate(riddle, riddle.at(monkey1));
        // std::cout << monkey2 << " = " << other << std::endl;
        return get_lhs_inverse_operator(opp)(target, other);
    }

    if (requires_monkey(riddle, monkey1, "humn")) {
        // target = dependent op other
        // dependent = target invop other
        dependent = monkey1;
        other = evaluate(riddle, riddle.at(monkey2));
        // std::cout << monkey2 << " = " << other << std::endl;
        return solve(riddle, dependent, get_rhs_inverse_operator(opp)(target, other));
    } else {
        // target = other op dependent
        // dependent = other invop target
        dependent = monkey2;
        other = evaluate(riddle, riddle.at(monkey1));
        // std::cout << monkey1 << " = " << other << std::endl;
        return solve(riddle, dependent, get_lhs_inverse_operator(opp)(target, other));
    }

    throw std::runtime_error("Control should never reach here!");
}

int part_b(const std::string &input) {
    Riddle riddle;
    parse_input(riddle, input);

    const auto &[monkey1, monkey2] = std::get<Expression>(riddle.at("root")).second;
    
    Monkey dependent;
    int64_t target;
    if (requires_monkey(riddle, monkey1, "humn")) {
        dependent = monkey1;
        target = evaluate(riddle, riddle.at(monkey2));
    } else {
        dependent = monkey2;
        target = evaluate(riddle, riddle.at(monkey1));
    }
    
    int64_t result = solve(riddle, dependent, target);
    std::cout << result << std::endl;

    riddle["humn"] = result;

    // std::cout << target << " : " << evaluate(riddle, riddle.at(dependent)) << std::endl;

    return result;
}

} // namespace aoc