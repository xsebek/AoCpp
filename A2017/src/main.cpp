#include <iostream>
#include "aocpp.h"
#include "day01.hpp"

int main() {
    aocpp();
    try {
        main01(std::cin);
    } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            return 1;
    }
    return 0;
}
