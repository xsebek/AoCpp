#include <iostream>
#include <algorithm>
#include <array>
#include <fmt/core.h>
#include <iomanip>
#include "day05.h"

void main05(std::istream &input) {
    auto data = parse05(input);
    std::cout << "Part 1: " << solve1(data) << std::endl;
    std::cout << "Part 1: " << solve2(data) << std::endl;
    //throw std::runtime_error("Day 05 part 2 not implemented!");
}

auto parse05(std::istream &input) -> std::vector<int> {
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

auto solve1(std::vector<int> data) -> int {
    //std::cout << "------------------------\n";
    auto pos = data.begin();
    for (int step = 0;; ++step) {
        if (pos < data.begin() || data.end() <= pos) {
            return step;
        }
        //debug(data, pos);
        pos += (*pos)++;
    }
}

auto solve2(std::vector<int> data) -> int {
    //std::cout << "------------------------\n";
    auto pos = data.begin();
    for (int step = 0;; ++step) {
        if (pos < data.begin() || data.end() <= pos) {
            return step;
        }
        //debug(data, pos);
        pos += (*pos >= 3) ? (*pos)-- : (*pos)++;
    }
}