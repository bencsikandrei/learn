#ifndef COMMONDEF_H
#define COMMONDEF_H

#include <QObject>

class CommonDefs : public QObject
{
    Q_OBJECT

public:
    enum class Heading
    {
        N = 0,
        E = 90,
        S = 180,
        V = 270
    };
    Q_ENUM(Heading)
};

#endif  // COMMONDEF_H
