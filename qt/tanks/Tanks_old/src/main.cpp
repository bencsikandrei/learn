#include <QGuiApplication>
#include <QQuickView>
#include "inc/boardtypesregisterer.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    QQuickView      view;

    BoardTypesRegisterer boardTypesRegisterer;
    boardTypesRegisterer.registerBoardTypes();

    QUrl path = QUrl::fromLocalFile("/Users/andreiz/work/1on1/qt/Tanks/resources/main.qml");
    view.setSource(path);
    view.show();

    return app.exec();
}
