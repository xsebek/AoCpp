//
// Created by sebeko on 9.1.23.
//
#ifndef AOCPP_DAY02_H
#define AOCPP_DAY02_H
#pragma once
#include <istream>
#include <vector>

void main02(std::istream &input);

auto parse02(std::istream &input) -> std::vector<std::vector<int>>;
auto parse02(const std::vector<std::string> &input) -> std::vector<std::vector<int>>;

auto diffMinMax(const std::vector<std::vector<int>>& data) -> int;

auto evenDivide(const std::vector<std::vector<int>>& data) -> int;

#endif //AOCPP_DAY02_H
