#include "../inc/tankcontroller.h"

TankController::TankController(QObject* parent)
    : QObject(parent)
    , m_posX(-1)
    , m_posY(-1)
    , m_stepSize(5)
    , m_roomController(800, 640)
{
    resetToDefaultPosition();
}

void TankController::moveUp()
{
    if (m_roomController.isMoveUpValid(m_posY, m_stepSize))
    {
        setPosY(m_posY - m_stepSize);
    }
}

void TankController::moveDown()
{
    if (m_roomController.isMoveDownValid(m_posY, m_stepSize, 50))
    {
        setPosY(m_posY + m_stepSize);
    }
}

void TankController::moveLeft()
{
    if (m_roomController.isMoveLeftValid(m_posX, m_stepSize))
    {
        setPosX(m_posX - m_stepSize);
    }
}

void TankController::moveRight()
{
    if (m_roomController.isMoveRightValid(m_posX, m_stepSize, 50))
    {
        setPosX(m_posX + m_stepSize);
    }
}

void TankController::resetToDefaultPosition()
{
    m_posX = 400;  // to change
    m_posY = 300;  // to change
}

int TankController::posX()
{
    return m_posX;
}

int TankController::posY()
{
    return m_posY;
}

int TankController::stepSize() const
{
    return m_stepSize;
}

// setters
void TankController::setPosX(const int x)
{
    if (m_posX != x)
    {
        m_posX = x;
        emit posXChanged();
    }
}

void TankController::setPosY(const int y)
{
    if (m_posY != y)
    {
        m_posY = y;
        emit posYChanged();
    }
}

void TankController::setStepSize(const int stepSize)
{
    m_stepSize = stepSize;
    emit stepSizeChanged();
}
