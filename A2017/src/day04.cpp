#include <iostream>
#include <algorithm>
#include <array>
#include <fmt/core.h>
#include <iomanip>
#include "day04.h"

void main04(std::istream &input) {
    auto data = parse04(input);
    std::cout << "Part 1: " << solve1(data) << std::endl;
    std::cout << "Part 1: " << solve2(data) << std::endl;
    //throw std::runtime_error("Day 04 part 2 not implemented!");
}

auto parse04(std::istream &input) -> std::vector<passphrase> {
    auto res = std::vector<passphrase>();
    auto line = std::string();
    while (std::getline(input, line)) {
        auto word = std::string();
        auto in_line = std::istringstream(line);
        res.emplace_back(std::istream_iterator<std::string>(in_line), std::istream_iterator<std::string>());
    }
    return res;
}

auto solve1(const std::vector<passphrase> &data) -> int {
    return static_cast<int>(std::ranges::count_if(data, [](const auto &pass){
        return std::ranges::all_of(pass, [&pass](auto w) {
            return std::ranges::count(pass, w) == 1;
        });
    }));
}

auto solve2(const std::vector<passphrase> &data) -> int {
    auto count_anagrams = [](const auto &words, auto w) {
        std::ranges::sort(w);
        return std::ranges::count_if(words, [&w](auto w2){
            std::ranges::sort(w2);
            return w == w2;
        });
    };
    return static_cast<int>(std::ranges::count_if(data, [&](const auto &pass){
        return std::ranges::all_of(pass, [&](const auto &w) {
            return count_anagrams(pass, w) == 1;
        });
    }));
}