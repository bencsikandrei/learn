#ifndef BULLETCONTROLLER_H
#define BULLETCONTROLLER_H

#include "roomcontroller.h"
#include "commondef.h"

#include <QObject>
#include <QTimer>

class BulletController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int posX READ posX WRITE setPosX NOTIFY posXChanged)
    Q_PROPERTY(int posY READ posY WRITE setPosY NOTIFY posYChanged)
    Q_PROPERTY(CommonDefs::Heading heading WRITE setHeading NOTIFY headingChanged)
    Q_PROPERTY(int stepSize READ stepSize WRITE setStepSize NOTIFY stepSizeChanged)

public:
    explicit BulletController(QObject* parent = nullptr);
    ~BulletController();

    // actions
    Q_INVOKABLE void moveUp();
    Q_INVOKABLE void moveDown();
    Q_INVOKABLE void moveLeft();
    Q_INVOKABLE void moveRight();

    // getters
    int posX();
    int posY();
    int stepSize() const;

    // setters
    void setPosX(const int x);
    void setPosY(const int y);
    void setStepSize(const int stepSize);
    void setHeading(const CommonDefs::Heading newHeading);

private:
    int                 m_posX;
    int                 m_posY;
    int                 m_stepSize;
    RoomController      m_roomController;
    QTimer              m_timer;
    CommonDefs::Heading m_heading;

    void onTimeout();

signals:
    void posXChanged();
    void posYChanged();
    void stepSizeChanged();
    void objectHit();
    void headingChanged();
};

#endif  // BULLETCONTROLLER_H
