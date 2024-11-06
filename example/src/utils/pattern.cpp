#include "pattern.hpp"
#include <iostream>
#include <string>

namespace utils {
    void printPattern(int rows, char symbol) {
        for (int i = 0; i < rows; i++) {
            std::cout << std::string(rows - i - 1, ' ');
            std::cout << std::string(2 * i + 1, symbol) << std::endl;
        }
    }
} 