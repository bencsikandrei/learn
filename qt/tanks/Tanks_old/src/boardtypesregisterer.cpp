#include "QtQml"
#include "../inc/tankcontroller.h"
#include "../inc/bulletcontroller.h"
#include "../inc/boardtypesregisterer.h"
#include "../inc/commondef.h"

void BoardTypesRegisterer::registerBoardTypes()
{
    qmlRegisterType<TankController>("boardItems", 1, 0, "TankController");
    qmlRegisterType<BulletController>("boardItems", 1, 0, "BulletController");
    qmlRegisterType<CommonDefs>("boardItems", 1, 0, "CommonDefs");
}
