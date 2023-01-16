#include <iostream>
#include <algorithm>
#include <array>
#include <utility>
#include <fmt/core.h>
#include "day06.h"

namespace day06 {

void main(std::istream &input) {
    auto data = parse(input);
    auto s12 = solve12(data);
    std::cout << "Part 1: " << s12.first << std::endl;
    std::cout << "Part 1: " << s12.second << std::endl;
    //throw std::runtime_error("Day 06 part 2 not implemented!");
}

auto parse(std::istream &input) -> std::vector<int> {
    auto res = std::vector<int>();
    int tmp;
    while (input >> tmp) {
        res.push_back(tmp);
    }
    return res;
}

[[maybe_unused]]
void debug(auto &data, auto i) {
    for (auto j = data.begin(); j < data.end(); ++j) {
        if (i == j) {
            std::cout << " (" << *i << ")";
        } else {
            std::cout << "  " << *j << " ";
        }
    }
    std::cout << std::endl;
}

auto solve12(std::vector<int> data) -> std::pair<int,int> {
    //std::cout << "------------------------\n";
    using position = decltype(data);
    auto positions = std::vector<position>();
    for (int step = 0;; ++step) {
        auto prev = std::ranges::find(positions, data);
        if (prev != positions.end()) {
            return {step, static_cast<int>(positions.end() - prev)};
        }
        positions.push_back(data);
        // find and redistribute
        auto p = std::ranges::max_element(data);
        //debug(data, p);
        auto max = *p;
        *p = 0;
        for (int i = max; i > 0; --i) {
            if (++p == data.end()) {
                p = data.begin();
            }
            *p += 1;
            //std::cout << ">";
            //debug(data, p);
        }
    }
}

auto solve1(std::vector<int> data) -> int {
    return solve12(std::move(data)).first;
}

auto solve2(std::vector<int> data) -> int {
    return solve12(std::move(data)).second;
}

} // namespace day06