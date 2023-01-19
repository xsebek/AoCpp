#include <algorithm>
#include <fmt/core.h>
#include <lexy/callback.hpp>
#include <lexy/dsl.hpp>
#include <lexy/callback/container.hpp>
#include <lexy/input/string_input.hpp>
#include <lexy_ext/report_error.hpp>
#include <lexy/action/parse.hpp>
#include <iostream>
#include <map>
#include <ranges>
#include "day07.h"

namespace day07 {

void main(std::istream &input) {
    auto data = parse({std::istreambuf_iterator<char>(input), {}});
    std::cout << "Part 1: " << solve1(data) << std::endl;
    std::cout << "Part 1: " << solve2(data) << std::endl;
    // throw std::runtime_error("Day 07 part 2 not implemented!");
}

namespace grammar {
namespace dsl = lexy::dsl;

struct word {
    static constexpr auto rule = dsl::identifier(dsl::ascii::alpha);
    static constexpr auto value = lexy::as_string<std::string>;
};

struct word_list {
    static constexpr auto rule = dsl::list(dsl::p<word>, dsl::sep(dsl::comma));
    static constexpr auto value = lexy::as_list<std::vector<std::string>>;
};

struct program {
    static constexpr auto rule =
            dsl::p<word> +
            dsl::round_bracketed(dsl::integer<int>) +
            dsl::opt(dsl::lit<"->"> >> dsl::p<word_list>);
    static constexpr auto value = lexy::construct<Program>;
};

struct program_list {
    static constexpr auto whitespace = dsl::ascii::blank; // skip ' ' and '\t', but not '\n', '\r'
    static constexpr auto rule = dsl::terminator(dsl::eof).list(dsl::p<program> + dsl::if_(dsl::newline));
    static constexpr auto value = lexy::as_list<std::vector<Program>>;
};
} // namespace grammar

auto parse(const std::string &input) -> std::vector<Program> {
    auto l_input = lexy::string_input<lexy::ascii_encoding>(input);
    auto result = lexy::parse<grammar::program_list>(l_input, lexy_ext::report_error);
    if (result.has_value()) {
        return result.value();
    }
    throw std::runtime_error("Could not parse program");
}

auto preprocess(const std::vector<Program> &data) -> std::map<std::string, Program> {
    auto named_programs = std::views::transform(data, [](auto p){
        return std::pair(p.name, p);
    });
    auto programs = std::map<std::string, Program>{named_programs.begin(), named_programs.end()};
    for (auto &p: data) {
        for (auto &a: p.above) {
            programs.at(a).below = p.name;
        }
    }
    return programs;
}

auto solve1(const std::vector<Program> &data) -> std::string {
    auto programs = preprocess(data);
    auto root = std::ranges::find_if(programs, [](const auto &p){
        return p.second.below.empty();
    });
    return (root != programs.end()) ? root->first : "<not found>";
}


auto total_weight(std::map<std::string, Program> &programs, Program &p) -> int {
    for (const auto &a: p.above) {
        p.child_weight += total_weight(programs, programs.at(a));
    }
    return p.weight + p.child_weight;
}

auto find_unbalanced(int depth, std::map<std::string, Program> &programs, Program &p, int expected) -> std::pair<std::string, int> {
    //fmt::print("{: >{}}: {} ({}) expected total {} for node {}  [", "find", depth+4, p.name, p.weight, expected, expected-p.child_weight);
    auto weight = [&programs](const std::string &a) -> int {
        auto &pa = programs.at(a);
        return pa.weight + pa.child_weight;
    };
    //for (const auto &a : p.above) {
    //    fmt::print(" {}({}),", a, weight(a));
    //}
    auto lowest = std::ranges::min_element(p.above, {}, weight);
    auto greatest = std::ranges::max_element(p.above, {}, weight);
    //fmt::print("]  lowest: {} greatest: {}\n", *lowest, *greatest);
    if (lowest == greatest) {
        return {p.name, expected - p.child_weight};
    }
    auto same_as = [weight](const std::string &n){
        return [w = weight(n), weight, n](const std::string &a) {
            return n != a && weight(a) == w;
        };
    };
    if (std::ranges::none_of(p.above, same_as(*lowest))) {
        return find_unbalanced(depth+1, programs, programs.at(*lowest), weight(*greatest));
    }
    if (std::ranges::none_of(p.above, same_as(*greatest))) {
        return find_unbalanced(depth+1, programs, programs.at(*greatest), weight(*lowest));
    }
    throw std::runtime_error("no single unbalanced node");
}

auto solve2(const std::vector<Program> &data) -> int {
    auto programs = preprocess(data);
    auto &root = std::ranges::find_if(programs, [](const auto &p){
        return p.second.below.empty();
    })->second;
    auto rw = total_weight(programs, root);
    auto [n, w] = find_unbalanced(0, programs, root, rw);
    //fmt::print("{}: {}\n", n, w);
    return w;
}

bool Program::operator==(const Program &rhs) const {
    return name == rhs.name &&
           weight == rhs.weight &&
           above == rhs.above;
}

bool Program::operator!=(const Program &rhs) const {
    return !(rhs == *this);
}
} // namespace day07