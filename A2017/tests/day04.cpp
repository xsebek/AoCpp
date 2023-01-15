//
// Created by sebeko on 9.1.23.
//
#include <gtest/gtest.h>
#include "../src/day04.h"

TEST(Day04, parse) {
    auto inputs = std::istringstream(
            "aa bb cc dd ee\n"
            "aa bb cc dd aa\n"
            "aa bb cc dd aaa\n");
    auto res = std::vector<passphrase>{
            {"aa", "bb", "cc", "dd", "ee"},
            {"aa", "bb", "cc", "dd", "aa"},
            {"aa", "bb", "cc", "dd", "aaa"}
    };
    EXPECT_EQ(parse04(inputs), res);
}

TEST(Day04, part1) {
    auto inputs = std::istringstream(
            "aa bb cc dd ee\n"
            "aa bb cc dd aa\n"
            "aa bb cc dd aaa\n");
    EXPECT_EQ(solve1(parse04(inputs)), 2);
}

TEST(Day04, part2) {
    auto inputs = std::istringstream(
            "abcde fghij\n"
            "abcde xyz ecdab\n"
            "a ab abc abd abf abj\n"
            "iiii oiii ooii oooi oooo\n"
            "oiii ioii iioi iiio\n");
    EXPECT_EQ(solve2(parse04(inputs)), 3);}