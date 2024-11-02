#pragma once
#include "point.hpp"

namespace geometry {
    class Shape {
    public:
        virtual ~Shape() = default;
        virtual double area() const = 0;
        virtual double perimeter() const = 0;
        virtual void print() const = 0;
    };

    class Circle : public Shape {
    public:
        Circle(const Point& center, double radius);
        double area() const override;
        double perimeter() const override;
        void print() const override;
        
    private:
        Point center;
        double radius;
    };
} 