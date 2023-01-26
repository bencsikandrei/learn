#ifndef ROOMCONTROLLER_H
#define ROOMCONTROLLER_H

class RoomController
{
public:
    RoomController(const int width, const int height);
    ~RoomController();

    bool isMoveUpValid(const int pos, const int stepSize);
    bool isMoveLeftValid(const int pos, const int stepSize);
    bool isMoveDownValid(const int pos, const int stepSize, const int tankSize);
    bool isMoveRightValid(const int pos, const int stepSize, const int tankSize);

private:
    int m_width;
    int m_height;
};

#endif  // ROOMCONTROLLER_H
