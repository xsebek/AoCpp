#include <gtest/gtest.h>
#include "../src/day01.hpp"

TEST(Day01, trivial) {
		EXPECT_TRUE(true);
}

TEST(Day01, sanity) {
    std::istringstream i("1122");
    int x;
    i >> x;
    EXPECT_EQ(x, 1122);
}

TEST(Day01, parse) {
    std::istringstream i("1122");
    std::vector<int> res({1,1,2,2});
    EXPECT_EQ(parse01(i), res);
    EXPECT_EQ(parse01("1122"), res);
}

TEST(Day01, part1) {
    EXPECT_EQ(sum_next({1,1,2,2}), 3);
    EXPECT_EQ(sum_next({1,1,1,1}), 4);
    EXPECT_EQ(sum_next({1,2,3,4}), 0);
    EXPECT_EQ(sum_next({9,1,2,1,2,1,2,9}), 9);
}

TEST(Day01, part2) {
    EXPECT_EQ(sum_half(parse01("1212")), 6);
    EXPECT_EQ(sum_half(parse01("1221")), 0);
    EXPECT_EQ(sum_half(parse01("123425")), 4);
    EXPECT_EQ(sum_half(parse01("123123")), 12);
    EXPECT_EQ(sum_half(parse01("12131415")), 4);
}