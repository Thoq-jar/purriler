#pragma once

namespace geometry {
    class Shape {
    public:
        virtual double area() const = 0;
        virtual double perimeter() const = 0;
        virtual void print() const = 0;
        virtual ~Shape() = default;
    };
} 