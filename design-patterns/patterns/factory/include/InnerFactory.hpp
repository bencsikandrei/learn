#pragma once

class Point {
  public:
    float X{}, Y{};

    class Factory {
      public:
        static Point fromCartesian(float x, float y);
        static Point fromPolar(float rho, float theta);
    };

  private:
    Point(float a, float b);
};
