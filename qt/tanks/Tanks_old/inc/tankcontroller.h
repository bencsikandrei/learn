#ifndef TANKCONTROLLER_H
#define TANKCONTROLLER_H

#include "roomcontroller.h"

#include <QObject>

class TankController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int posX READ posX NOTIFY posXChanged)
    Q_PROPERTY(int posY READ posY NOTIFY posYChanged)
    Q_PROPERTY(int stepSize READ stepSize WRITE setStepSize NOTIFY stepSizeChanged)

public:
    explicit TankController(QObject* parent = nullptr);

    // actions
    Q_INVOKABLE void moveUp();
    Q_INVOKABLE void moveDown();
    Q_INVOKABLE void moveLeft();
    Q_INVOKABLE void moveRight();
    Q_INVOKABLE void resetToDefaultPosition();

    // getters
    int posX();
    int posY();
    int stepSize() const;

    // setters
    void setPosX(const int x);
    void setPosY(const int y);
    void setStepSize(const int stepSize);

private:
    int            m_posX;
    int            m_posY;
    int            m_stepSize;
    RoomController m_roomController;

signals:
    void posXChanged();
    void posYChanged();
    void stepSizeChanged();

public slots:
};

#endif  // TANKCONTROLLER_H
