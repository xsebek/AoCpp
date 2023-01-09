//
// Created by sebeko on 9.1.23.
//
#include <iostream>
#include <algorithm>
#include "day02.h"

void main02(std::istream &input) {
    auto data = parse02(input);
    std::cout << "Part 1: " << diffMinMax(data) << std::endl;
    std::cout << "Part 2: " << evenDivide(data) << std::endl;
    //throw std::runtime_error("Day 02 part 2 not implemented!");
}

auto parse02(std::istream &input) -> std::vector<std::vector<int>> {
    auto buf = std::vector<std::string>();
    auto line = std::string();
    while (std::getline(input, line)) {
        buf.emplace_back(std::move(line));
    }
    return parse02(buf);
}

auto parse02(const std::vector<std::string> &input) -> std::vector<std::vector<int>> {
    auto res = std::vector<std::vector<int>>();
    auto delimiter = std::string("\t");
    for (const auto &s: input) {
        size_t last = 0, next;
        auto &line = res.emplace_back();
        while ((next = s.find(delimiter, last)) != std::string::npos) {
            //std::cout << "\t" << s.substr(last, next - last);
            line.push_back(std::stoi(s.substr(last, next - last)));
            last = next + 1;
        }
        //std::cout << "\t" << s.substr(last) << std::endl;
        line.push_back(std::stoi(s.substr(last)));
    }
    return res;
}

auto diffMinMax(const std::vector<std::vector<int>>& data) -> int {
    int sum = 0;
    for (const auto &line: data) {
        auto [imin,imax] = std::ranges::minmax_element(line);
        sum += std::abs(*imin - *imax);
    }
    return sum;
}

template <typename T>
struct combinations {
    struct iterator {
        using value_type = std::pair<T, T>;
        std::vector<T>::const_iterator x;
        std::vector<T>::const_iterator y;
        std::vector<T>::const_iterator b;
        std::vector<T>::const_iterator e;

        bool operator!=(const typename combinations<T>::iterator &j) {
            return (x != j.x) || (y != j.y);
        }

        combinations<T>::iterator operator++() {
            ++y;
            if (x == y) {
                ++y;
            }
            if (y == e) {
                y = b;
                ++x;
            }
            return *this;
        }

        value_type operator*() const {
            return {*x, *y};
        }
    };

    const iterator i;

    combinations(const std::vector<T> &v)
    : i({v.cbegin(), ++v.cbegin(), v.cbegin(), v.cend()})
    {};

    iterator begin() {
        return i;
    }

    iterator end() {
        return {i.e, i.e, i.b, i.e};
    }
};

auto evenDivide(const std::vector<std::vector<int>> &data) -> int {
    int sum = 0;
    for (const auto &line: data) {
        bool found = false;
        for (auto [x,y]: combinations(line)) {
            std::cout << "x:\t" << x << "\ty:\t" << y;
            if (x % y == 0) {
                sum += x / y;
                found = true;
                std::cout << "\tDIVIDE!\n";
                break;
            }
            std::cout << "\tNOPE\n";
        }
        if (!found) {
            std::cerr << "Did not find evenly dividing values in line!\n";
        }
        std::cout << std::endl;
    }
    return sum;}

