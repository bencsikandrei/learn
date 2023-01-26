#include "../inc/roomcontroller.h"

RoomController::RoomController(const int width, const int height)
    : m_width(width)
    , m_height(height)
{
}

RoomController::~RoomController()
{
}

bool RoomController::isMoveUpValid(const int pos, const int stepSize)
{
    return (pos - stepSize >= 0);
}

bool RoomController::isMoveLeftValid(const int pos, const int stepSize)
{
    return (pos - stepSize >= 0);
}

bool RoomController::isMoveDownValid(const int pos, const int stepSize, const int tankSize)
{
    return (pos + stepSize <= m_height - tankSize);
}

bool RoomController::isMoveRightValid(const int pos, const int stepSize, const int tankSize)
{
    return (pos + stepSize <= m_width - tankSize);
}
