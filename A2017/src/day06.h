#ifndef AOCPP_DAY06_H
#define AOCPP_DAY06_H
#pragma once
#include <istream>
#include <vector>

namespace day06 {

void main(std::istream &input);

auto parse(std::istream &input) -> std::vector<int>;

auto solve12(std::vector<int> data) -> std::pair<int,int>;

auto solve1(std::vector<int> data) -> int;

auto solve2(std::vector<int> data) -> int;

} // namespace day06
#endif //AOCPP_DAY06_H
