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

auto evenDivide(const std::vector<std::vector<int>> &data) -> int {
    int sum = 0;
    for (const auto &line: data) {
        bool found = false;
        for (size_t x = 0; x < line.size(); ++x) {
            for (size_t y = 0; y < line.size(); ++y) {
                if (x == y) {
                    continue;
                }
                std::cout << "x:\t" << line[x] << "\ty:\t" << line[y];
                if (line[x] % line[y] == 0) {
                    sum += line[x] / line[y];
                    found = true;
                    std::cout << "\tDIVIDE!\n";
                    break;
                }
                std::cout << "\tNOPE\n";
            }
            if (found) {
                break;
            }
        }
        if (!found) {
            std::cerr << "Did not find evenly dividing values in line!\n";
        }
        std::cout << std::endl;
    }
    return sum;}

