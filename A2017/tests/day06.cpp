#include <gtest/gtest.h>
#include "../src/day06.h"

TEST(Day06, parse) {
    auto inputs = std::istringstream("0\t2\t7\t0");
    auto res = std::vector<int>{0,2,7,0};
    EXPECT_EQ(day06::parse(inputs), res);
}

TEST(Day06, part1) {
    EXPECT_EQ(day06::solve1({0,2,7,0}), 5);
}

TEST(Day06, part2) {
    EXPECT_EQ(day06::solve2({0,2,7,0}), 4);
}
