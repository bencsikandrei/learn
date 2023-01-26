#include <InnerFactory.hpp>
#include <cmath>

Point Point::Factory::fromCartesian(float x, float y) {
    Point p(x, y);
    return p;
}

Point Point::Factory::fromPolar(float rho, float theta) {
    Point p(rho * cos(theta), rho * sin(theta));
    return p;
}

Point::Point(float a, float b) : X{a}, Y{b} {}
