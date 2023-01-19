#ifndef AOCPP_DAY07_H
#define AOCPP_DAY07_H
#pragma once
#include <istream>
#include <vector>
#include <optional>

namespace day07 {

void main(std::istream &input);

struct Program {
    std::string name;
    int weight;
    std::vector<std::string> above;
    /// added parent in part 1
    std::string below;

    constexpr Program(std::string name, int weight, std::optional<std::vector<std::string>> above=std::nullopt)
            : name(std::move(name))
            , weight(weight)
            , above(above ? std::move(*above) : std::vector<std::string>())
    {}

    bool operator==(const Program &rhs) const;
    bool operator!=(const Program &rhs) const;
};

auto parse(const std::string &input) -> std::vector<Program>;

auto solve1(const std::vector<Program> &data) -> std::string;

// auto solve2(std::vector<Program> data) -> int;

} // namespace day07
#endif //AOCPP_DAY07_H
