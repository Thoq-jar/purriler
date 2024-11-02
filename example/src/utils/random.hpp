#pragma once
#include <vector>
#include <random>

namespace utils {
    template<typename T>
    std::vector<T> generateRandomVector(size_t size, T min, T max);
} 