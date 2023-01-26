#ifndef POSITION_H
#define POSITION_H

class Position
{
public:
    Position(const double& x, const double& y);

    // getters
    double getX() const;

    double getY() const;

    // setters
    void setX(const double& x);

    void setY(const double& y);

private:
    double m_x;
    double m_y;
};

#endif  // POSITION_H
