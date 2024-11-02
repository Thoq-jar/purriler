#include "random.hpp"
#include <random>

namespace utils {
    // Template implementation
    template<typename T>
    std::vector<T> generateRandomVector(size_t size, T min, T max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        
        // Use uniform_real_distribution for floating point types, uniform_int_distribution for integral types
        std::conditional_t<std::is_floating_point_v<T>,
            std::uniform_real_distribution<T>,
            std::uniform_int_distribution<T>> dis(min, max);
        
        std::vector<T> result;
        result.reserve(size);
        
        for (size_t i = 0; i < size; ++i) {
            result.push_back(dis(gen));
        }
        
        return result;
    }

    // Explicit template instantiations for the types we need
    template std::vector<int> generateRandomVector(size_t, int, int);
    template std::vector<float> generateRandomVector(size_t, float, float);
    template std::vector<double> generateRandomVector(size_t, double, double);
} 