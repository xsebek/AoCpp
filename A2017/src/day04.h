#ifndef AOCPP_DAY04_H
#define AOCPP_DAY04_H
#pragma once
#include <istream>
#include <vector>

void main04(std::istream &input);

using passphrase = std::vector<std::string>;

auto parse04(std::istream &input) -> std::vector<passphrase>;

auto solve1(const std::vector<passphrase> &data) -> int;

auto solve2(const std::vector<passphrase> &data) -> int;

#endif //AOCPP_DAY04_H
