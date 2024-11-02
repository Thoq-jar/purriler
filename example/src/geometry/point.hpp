#pragma once

namespace geometry {
    class Point {
    public:
        Point(double x = 0, double y = 0);
        double getX() const;
        double getY() const;
        void setX(double x);
        void setY(double y);
        
    private:
        double x, y;
    };
} 