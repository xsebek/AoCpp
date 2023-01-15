#include <gtest/gtest.h>
#include "../src/day05.h"

TEST(Day05, parse) {
    auto inputs = std::istringstream(
            "0\n"
            "3\n"
            "0\n"
            "1\n"
            "-3\n");
    auto res = std::vector<int>{0,3,0,1,-3};
    EXPECT_EQ(parse05(inputs), res);
}

TEST(Day05, part1) {
    EXPECT_EQ(solve1({0,3,0,1,-3}), 5);
}

TEST(Day05, part2) {
    EXPECT_EQ(solve2({0,3,0,1,-3}), 10);
}
