#include <gtest/gtest.h>
#include "../src/day07.h"



const auto input = std::string(
    "pbga (66)\n"
    "xhth (57)\n"
    "ebii (61)\n"
    "havc (66)\n"
    "ktlj (57)\n"
    "fwft (72) -> ktlj, cntj, xhth\n"
    "qoyq (66)\n"
    "padx (45) -> pbga, havc, qoyq\n"
    "tknk (41) -> ugml, padx, fwft\n"
    "jptl (61)\n"
    "ugml (68) -> gyxo, ebii, jptl\n"
    "gyxo (61)\n"
    "cntj (57)\n"
    );

TEST(Day07, parse) {
    const auto simple_input = std::string(
            "ktlj (57)\n"
            "fwft (72) -> ktlj, cntj, xhth\n"
    );
    auto res = std::vector<day07::Program>{
            {"ktlj", 57},
            {"fwft", 72, {{"ktlj", "cntj", "xhth"}}},
    };
    EXPECT_EQ(day07::parse(simple_input), res);
    EXPECT_FALSE(day07::parse(input).empty());
}

TEST(Day07, part1) {
    EXPECT_EQ(day07::solve1(day07::parse(input)), "tknk");
}

TEST(Day07, part2) {
    EXPECT_EQ(day07::solve2(day07::parse(input)), 60);
}
