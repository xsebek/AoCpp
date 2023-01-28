#include <gtest/gtest.h>
#include "../src/day08.h"



const auto input = std::string(
    "ba inc 5 if a > 1\n"
    "a inc 1 if ba < 5\n"
    "c dec -10 if a >= 1\n"
    "c inc -20 if c == 10\n"
    );

TEST(Day08, parse) {
    const auto simple_input = std::string(
            "b inc 5 if a > 1\n"
    );
    auto res = day08::Program{
            {"b", "inc", 5, {"a", day08::Comparison::GT, 1}}
    };
    EXPECT_EQ(day08::parse(simple_input), res);
    EXPECT_FALSE(day08::parse(input).empty());
    for (const auto &i: day08::parse(input)) {
        std::cout << i << std::endl;
    }
}

TEST(Day08, part1) {
    EXPECT_EQ(day08::solve1(day08::parse(input)), 1);
}

TEST(Day08, part2) {
    EXPECT_EQ(day08::solve2(day08::parse(input)), 10);
}
