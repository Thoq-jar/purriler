#include "circle.hpp"
#include <iostream>
#include <cmath>

namespace geometry {
    Circle::Circle(const Point& center, double radius) 
        : center(center), radius(radius) {}
    
    double Circle::area() const {
        return M_PI * radius * radius;
    }
    
    double Circle::perimeter() const {
        return 2 * M_PI * radius;
    }
    
    void Circle::print() const {
        std::cout << "Circle at (" << center.getX() << ", " 
                  << center.getY() << ") with radius " << radius;
    }
} 