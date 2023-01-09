#pragma once
#include <istream>
#include <vector>

void main01(std::istream &input);

auto parse01(std::istream &input) -> std::vector<int>;
auto parse01(const std::string &input) -> std::vector<int>;

auto sum_next(const std::vector<int> &data) -> int;

auto sum_half(const std::vector<int> &data) -> int;
