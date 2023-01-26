#include <Factory.hpp>
#include <cmath>

Point PointFactory::fromCartesian(float x, float y) {
    Point p(x, y);
    return p;
}

Point PointFactory::fromPolar(float rho, float theta) {
    Point p(rho * cos(theta), rho * sin(theta));
    return p;
}

Point::Point(float a, float b) : X{a}, Y{b} {}
