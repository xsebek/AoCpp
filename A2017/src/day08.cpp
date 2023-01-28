#include <algorithm>
#include <fmt/core.h>
#include <lexy/callback.hpp>
#include <lexy/dsl.hpp>
#include <lexy/callback/container.hpp>
#include <lexy/input/string_input.hpp>
#include <lexy_ext/report_error.hpp>
#include <lexy/action/parse.hpp>
#include <iostream>
#include "day08.h"

namespace day08 {

void main(std::istream &input) {
    auto data = parse({std::istreambuf_iterator<char>(input), {}});
    std::cout << "Part 1: " << solve1(data) << std::endl;
    std::cout << "Part 2: " << solve2(data) << std::endl;
    //throw std::runtime_error("Day 08 part 2 not implemented!");
}

namespace grammar {
namespace dsl = lexy::dsl;

struct word {
    static constexpr auto rule = dsl::identifier(dsl::ascii::alpha);
    static constexpr auto value = lexy::as_string<std::string>;
};

struct signed_integer {
    static constexpr auto rule  = dsl::sign + dsl::integer<int>;
    static constexpr auto value = lexy::as_integer<int>;
};

struct comparison {
    static constexpr auto entities = lexy::symbol_table<Comparison>
            .map<LEXY_SYMBOL("==")>(Comparison::EQ)
            .map<LEXY_SYMBOL("!=")>(Comparison::NEQ)
            .map<LEXY_SYMBOL(">")>(Comparison::GT)
            .map<LEXY_SYMBOL(">=")>(Comparison::GE)
            .map<LEXY_SYMBOL("<")>(Comparison::LT)
            .map<LEXY_SYMBOL("<=")>(Comparison::LE);
    static constexpr auto rule = dsl::symbol<entities>(dsl::identifier(dsl::ascii::punct));
    static constexpr auto value = lexy::forward<Comparison>;
};

struct condition {
    static constexpr auto rule =
            dsl::lit<"if"> >>
            dsl::p<word> +
            dsl::p<comparison> +
            dsl::p<signed_integer>;
    static constexpr auto value = lexy::construct<Condition>;
};

struct instruction {
    static constexpr auto rule =
            dsl::p<word> +
            dsl::p<word> +
            dsl::p<signed_integer> +
            dsl::p<condition>;
    static constexpr auto value = lexy::construct<Instruction>;
};

struct program {
    static constexpr auto whitespace = dsl::ascii::blank; // skip ' ' and '\t', but not '\n', '\r'
    static constexpr auto rule = dsl::terminator(dsl::eof).list(dsl::p<instruction> + dsl::if_(dsl::newline));
    static constexpr auto value = lexy::as_list<Program>;
};

} // namespace grammar

auto parse(const std::string &input) -> Program {
    auto l_input = lexy::string_input<lexy::ascii_encoding>(input);
    auto result = lexy::parse<grammar::program>(l_input, lexy_ext::report_error);
    if (result.has_value()) {
        return result.value();
    }
    throw std::runtime_error("Could not parse program");
}

auto solve1(const Program &data) -> int {
    auto registers = Registers();
    for (const auto &i: data) {
        i.eval(registers);
    }
    // int max = INT_MIN;
    // for (auto [k,v]: registers) {
    //     max = std::max(max, v);
    // }
    // return max;
    return std::ranges::max(std::ranges::views::values(registers));;
}

auto solve2(const Program &data) -> int {
    auto registers = Registers();
    int max = INT_MIN;
    for (const auto &i: data) {
        max = std::max(max, i.eval(registers));
    }
    return max;
}

std::string to_string(Comparison o) {
    switch (o) {
        case Comparison::EQ: return "==";
        case Comparison::NEQ: return "!=";
        case Comparison::LT: return "<";
        case Comparison::LE: return "<=";
        case Comparison::GT: return ">";
        case Comparison::GE: return ">=";
        default: return "???";
    }
}

auto to_fun(Comparison o) -> std::function<bool(int, int)> {
    switch (o) {
        case Comparison::EQ: return std::equal_to();
        case Comparison::NEQ: return std::not_equal_to();
        case Comparison::LT: return std::less();
        case Comparison::LE: return std::less_equal();
        case Comparison::GT: return std::greater();
        case Comparison::GE: return std::greater_equal();
        default: throw std::runtime_error("unknown comparison!");
    }
}

bool Condition::operator==(const Condition &rhs) const {
    return register_name == rhs.register_name &&
           binary_op == rhs.binary_op &&
           value == rhs.value;
}

bool Condition::operator!=(const Condition &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Condition &condition) {
    os << "register_name: " << condition.register_name << " binary_op: " << to_string(condition.binary_op)
       << " value: " << condition.value;
    return os;
}

bool Condition::eval(const Registers &registers) const {
    int r = registers.contains(register_name) ? registers.at(register_name) : 0;
    return to_fun(binary_op)(r, value);
}

bool Instruction::operator==(const Instruction &rhs) const {
    return register_name == rhs.register_name &&
           is_increment == rhs.is_increment &&
           amount == rhs.amount &&
           condition == rhs.condition;
}

bool Instruction::operator!=(const Instruction &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Instruction &instruction) {
    os << "register_name: " << instruction.register_name << " is_increment: " << instruction.is_increment
       << " amount: " << instruction.amount << " condition: (" << instruction.condition << ")";
    return os;
}

int Instruction::eval(Registers &registers) const {
    if (condition.eval(registers)) {
        return (registers[register_name] += (is_increment ? 1 : -1) * amount);
    }
    return registers[register_name];
}

} // namespace day08