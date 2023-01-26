#include "../inc/bulletcontroller.h"

BulletController::BulletController(QObject* parent)
    : QObject(parent)
    , m_posX(30)
    , m_posY(640)
    , m_stepSize(10)
    , m_roomController(800, 640)
{
    BulletController::connect(&m_timer, &QTimer::timeout, this, &BulletController::onTimeout);
    m_timer.start(50);
}

BulletController::~BulletController()
{
}

void BulletController::moveUp()
{
    if (m_roomController.isMoveUpValid(m_posY, m_stepSize))
    {
        setPosY(m_posY - m_stepSize);
    }
    else
    {
        emit objectHit();
    }
}

void BulletController::moveDown()
{
    if (m_roomController.isMoveDownValid(m_posY, m_stepSize, 50))
    {
        setPosY(m_posY + m_stepSize);
    }
}

void BulletController::moveLeft()
{
    if (m_roomController.isMoveLeftValid(m_posX, m_stepSize))
    {
        setPosX(m_posX - m_stepSize);
    }
}

void BulletController::moveRight()
{
    if (m_roomController.isMoveRightValid(m_posX, m_stepSize, 50))
    {
        setPosX(m_posX + m_stepSize);
    }
}

int BulletController::posX()
{
    return m_posX;
}

int BulletController::posY()
{
    return m_posY;
}

int BulletController::stepSize() const
{
    return m_stepSize;
}

// setters
void BulletController::setPosX(const int x)
{
    if (m_posX != x)
    {
        m_posX = x;
        emit posXChanged();
    }
}

void BulletController::setPosY(const int y)
{
    if (m_posY != y)
    {
        m_posY = y;
        emit posYChanged();
    }
}

void BulletController::setStepSize(const int stepSize)
{
    m_stepSize = stepSize;
    emit stepSizeChanged();
}

void BulletController::setHeading(const CommonDefs::Heading newHeading)
{
    m_heading = newHeading;
}

void BulletController::onTimeout()
{
    if (m_heading == CommonDefs::Heading::N && m_roomController.isMoveUpValid(m_posY, m_stepSize))
    {
        moveUp();
    }
    else if (m_heading == CommonDefs::Heading::S && m_roomController.isMoveDownValid(m_posY, m_stepSize, 50))
    {
        moveDown();
    }
    else if (m_heading == CommonDefs::Heading::E && m_roomController.isMoveRightValid(m_posY, m_stepSize, 50))
    {
        moveRight();
    }
    else if (m_heading == CommonDefs::Heading::V && m_roomController.isMoveLeftValid(m_posY, m_stepSize))
    {
        moveLeft();
    }
    else
    {
        m_timer.stop();
        emit objectHit();
    }
}
