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
    throw std::runtime_error("Day 07 part 2 not implemented!");
    // std::cout << "Part 1: " << s12.second << std::endl;
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

auto solve1(const std::vector<Program> &data) -> std::string {
    auto named_programs = std::views::transform(data, [](auto p){
        return std::pair(p.name, p);
    });
    auto programs = std::map<std::string, Program>{named_programs.begin(), named_programs.end()};
    for (auto &p: data) {
        for (auto &a: p.above) {
            programs.at(a).below = p.name;
        }
    }
    auto root = std::ranges::find_if(programs, [](const auto &p){ return p.second.below.empty(); });
    return (root != programs.end()) ? root->first : "<not found>";
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