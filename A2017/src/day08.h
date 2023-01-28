#ifndef AOCPP_DAY08_H
#define AOCPP_DAY08_H
#pragma once
#include <istream>
#include <vector>
#include <optional>
#include <ostream>
#include <map>
#include <ranges>
#include <functional>

namespace day08 {

void main(std::istream &input);

enum class Comparison {
    EQ, NEQ, LT, LE, GT, GE
};

std::string to_string(Comparison o);

auto to_fun(Comparison o) -> std::function<bool(int, int)>;

using Registers = std::map<std::string, int>;

struct Condition {
    std::string register_name;
    Comparison binary_op;
    int value;

    [[nodiscard]]
    bool eval(const Registers& registers) const;

    bool operator==(const Condition &rhs) const;
    bool operator!=(const Condition &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const Condition &condition);
};

struct Instruction {
    std::string register_name;
    bool is_increment;
    int amount;
    Condition condition;

    int eval(Registers &registers) const;

    Instruction(std::string r, std::string_view i, int a, Condition c)
    : register_name(std::move(r))
    , is_increment(i == "inc")
    , amount(a)
    , condition(std::move(c))
    {}



    bool operator==(const Instruction &rhs) const;

    bool operator!=(const Instruction &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Instruction &instruction);
};

using Program = std::vector<Instruction>;

auto parse(const std::string &input) -> Program;

auto solve1(const Program &data) -> int;

auto solve2(const Program &data) -> int;

} // namespace day08
#endif //AOCPP_DAY08_H
