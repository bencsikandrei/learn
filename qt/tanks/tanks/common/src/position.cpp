#include "position.h"

Position::Position(const double& x, const double& y)
    : m_x(x)
    , m_y(y)
{
}

void Position::setX(const double& x)
{
    m_x = x;
}

void Position::setY(const double& y)
{
    m_y = y;
}

double Position::getX() const
{
    return m_x;
}

double Position::getY() const
{
    return m_y;
}
