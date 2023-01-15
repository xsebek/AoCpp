//
// Created by sebeko on 9.1.23.
//
#include <iostream>
#include <algorithm>
#include <array>
#include <fmt/core.h>
#include <complex>
#include <ranges>
#include "day03.h"

void main03(std::istream &input) {
    auto data = parse03(input);
    std::cout << "Part 1: " << solve1(data) << std::endl;
    std::cout << "Part 1: " << solve2(data) << std::endl;
    //throw std::runtime_error("Day 03 part 1 not implemented!");
}

auto parse03(std::istream &input) -> int {
    int res;
    input >> res;
    return res;
}

auto layer_count(int n) -> int {
    for (int sum = 1, layer = 0;; ++layer) {
        sum += 2 * layer * 4;
        if (n <= sum) {
            return layer;
        }
    }
}

auto solve1(int num) -> int {
    int l = layer_count(num);
    auto s = Spiral(l);
    //std::cout << s;
    int i = 0;
    for (auto [x,y]: s) {
        s.set(x,y,++i);
        if (i == num) {
            //std::cout << s;
            return std::abs(x) + std::abs(y);
        }
    }
    return 0;
}

auto solve2(int num) -> int {
    int l = 1 + static_cast<int>(std::log10(num));
    auto s = Spiral(l);
    s.set(0,0,1);
    for (auto [x,y]: s) {
        int nsum = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                nsum += s.get(x+i,y+j);
            }
        }
        auto v = s.set(x,y,nsum);
        if (v > num) {
            //std::cout << s;
            return v;
        }
    }
    return 0;
}

std::ostream &operator<<(std::ostream &o, const Spiral &s) {
    int digits = s.max_val == 0 ? 1 : (1 + static_cast<int>(std::log10(s.max_val)));
    for (auto &l: std::ranges::views::reverse(s.grid)) {
        for (int x: l) {
            o << fmt::format("{:{}} ", x, digits);
        }
        o << "\n";
    }
    return o;
}

Spiral::out_iterator Spiral::out_iterator::operator++() {
    switch(leg){
        case 0: ++y; if(y  == layer + 1)  ++leg;                break;
        case 1: ++x; if(x  == layer + 1)  ++leg;                break;
        case 2: --y; if(-y == layer + 1)  ++leg;                break;
        case 3: --x; if(-x == layer + 1){ leg = 0; ++layer; }   break;
    }
    return *this;
}

bool Spiral::out_iterator::operator==(const Spiral::out_iterator &o) const {
    return (layer == o.layer) && (layer > border_layer || (x==o.x && y==o.y));
}

bool Spiral::out_iterator::operator!=(const Spiral::out_iterator &o) const {
    return !(*this == o);
}

int Spiral::set(ssize_t x, ssize_t y, int val) {
    //fmt::print("x: {}\ty: {}\t = {}\n", x, y, val);
    grid[x+layers][y+layers] = val;
    max_val = std::max(max_val, val);
    return val;
}

int Spiral::get(ssize_t x, ssize_t y) {
    return grid[x+layers][y+layers];
}
