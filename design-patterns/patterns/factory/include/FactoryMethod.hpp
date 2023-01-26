#pragma once

class Point {
  public:
    static Point newCartesian(float x, float y);
    static Point newPolar(float rho, float theta);

  public:
    float X{}, Y{};

  private:
    Point(float a, float b);
};
