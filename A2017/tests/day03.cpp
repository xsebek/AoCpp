//
// Created by sebeko on 9.1.23.
//
#include <gtest/gtest.h>
#include "../src/day03.h"

TEST(Day03, parse) {
    auto inputs = std::istringstream("1024");
    EXPECT_EQ(parse03(inputs), 1024);
}

TEST(Day03, part1) {
    EXPECT_EQ(layer_count(9), 1);
    EXPECT_EQ(layer_count(12), 2);
    EXPECT_EQ(solve1(12), 3);
    EXPECT_EQ(solve1(1024), 31);
}

TEST(Day03, part2) {
    EXPECT_EQ(solve2(800), 806);
}