#include <iostream>
#include <fstream>
#include "aocpp.h"
#include "day01.hpp"

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
        switch (day) {
            case 01:
                main01(input);
                return 0;
            case 02:
                // pass
                return 1;
            default:
                help();
                return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
