#include "day01.hpp"
#include <ranges>
#include <iostream>

void main01(std::istream &input) {
    auto data = parse01(input);
    std::cout << "Part 1: " << sum_next(data) << std::endl;
    std::cout << "Part 2: " << sum_half(data) << std::endl;
}

auto parse01(std::istream &input) -> std::vector<int> {
    auto data = std::vector<int>();
    for (char c; input >> c;) {
        // std::cout << c;
        data.push_back(c - '0');
    }
    // std::cout << std::endl;
    return data;
}

int sum_next(const std::vector<int> &data) {
    int sum = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        size_t j = (i+1) % data.size();
        if (data[i] == data[j]) {
            sum += data[i];
        }
    }
    return sum;
}

auto sum_half(const std::vector<int> &data) -> int {
    int sum = 0;
    size_t half = data.size()/2;
    for (size_t i = 0; i < data.size(); ++i) {
        size_t j = (i+half) % data.size();
        if (data[i] == data[j]) {
            sum += data[i];
        }
    }
    return sum;
}

auto parse01(const std::string &input) -> std::vector<int> {
    auto res = std::views::transform(input, [](char c){ return c - '0'; });
    return {res.begin(), res.end()};
}
