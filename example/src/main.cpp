#include "geometry/point.hpp"
#include "geometry/circle.hpp"
#include "utils/random.hpp"
#include "utils/pattern.hpp"
#include "analysis/number_analyzer.hpp"
#include <iostream>
#include <iomanip>
#include <memory>

using namespace geometry;
using namespace utils;
using namespace analysis;

int main() {
    std::cout << "=== Advanced C++ Feature Demo ===\n\n";
    
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(Point(0, 0), 5));
    shapes.push_back(std::make_unique<Circle>(Point(2, 3), 3));
    
    std::cout << "Shapes Information:\n";
    for (const auto& shape : shapes) {
        shape->print();
        std::cout << "Area: " << shape->area() << "\n";
        std::cout << "Perimeter: " << shape->perimeter() << "\n\n";
    }
    
    auto numbers = generateRandomVector<double>(10, 0.0, 100.0);
    std::cout << "Random Numbers:\n";
    for (const auto& num : numbers) {
        std::cout << std::fixed << std::setprecision(2) << num << " ";
    }
    std::cout << "\n\n";
    
    NumberAnalyzer analyzer;
    for (int i = 1; i <= 20; i++) {
        analyzer.addNumber(i % 5);
    }
    
    std::cout << "Number Analysis:\n";
    std::cout << "Average: " << analyzer.average() << "\n";
    std::cout << "Sum: " << analyzer.sum() << "\n";
    std::cout << "Frequency Distribution:\n";
    for (const auto& [num, freq] : analyzer.frequency()) {
        std::cout << num << ": " << std::string(freq, '*') << "\n";
    }
    
    std::cout << "\nDecorative Patterns:\n";
    printPattern(5, '#');
    std::cout << "\n";
    printPattern(7, '@');
    
    return 0;
}
