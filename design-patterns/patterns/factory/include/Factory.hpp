#pragma once

class Point {
  public:
    float X{}, Y{};

    Point(float a, float b);
};

class PointFactory {
  public:
    static Point fromCartesian(float x, float y);
    static Point fromPolar(float rho, float theta);
};
