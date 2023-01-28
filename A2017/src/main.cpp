#include <iostream>
#include <fstream>
#include "aocpp.h"
#include "day01.h"
#include "day02.h"
#include "day03.h"
#include "day04.h"
#include "day05.h"
#include "day06.h"
#include "day07.h"
#include "day08.h"

void help() {
    std::cout << "Run with day parameter: aocpp 01" << std::endl;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        help();
        return 1;
    }
    if (argv[1] == std::string("-h")) {
        help();
        return 0;
    }
    if (argv[1] == std::string("-v")) {
        aocpp();
        return 0;
    }
    auto day = std::strtoul(argv[1], nullptr, 10);
    try {
        auto input = std::ifstream(std::string("../input/2017/") + argv[1] + ".txt");
        auto days = std::vector{
                main01,
                main02,
                main03,
                main04,
                main05,
                day06::main,
                day07::main,
                day08::main,
        };
        if (day <= days.size()) {
            days[day - 1](input);
            return 0;
        } else {
            help();
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
