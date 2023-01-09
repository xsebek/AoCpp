//
// Created by sebeko on 9.1.23.
//
#include <gtest/gtest.h>
#include "../src/day02.h"

const auto input = std::string(
        "5\t1\t9\t5\n"
        "7\t5\t3\n"
        "2\t4\t6\t8");

const auto input2 = std::string(
        "5\t9\t2\t8\n"
        "9\t4\t7\t3\n"
        "3\t8\t6\t5");

TEST(Day02, parse) {
    auto inputs = std::istringstream(input);
    auto res = std::vector<std::vector<int>>(
            { {5, 1, 9, 5}
            , {7, 5, 3}
            , {2, 4, 6, 8}
            });
    EXPECT_EQ(parse02(inputs), res);
}

TEST(Day02, part1) {
    auto inputs = std::istringstream(input);
    EXPECT_EQ(diffMinMax(parse02(inputs)), 8 + 4 + 6);
}

TEST(Day02, part2) {
    auto inputs = std::istringstream(input2);
    EXPECT_EQ(evenDivide(parse02(inputs)), 4 + 3 + 2);
}