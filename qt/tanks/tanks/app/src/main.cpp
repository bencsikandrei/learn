#include <QGuiApplication>
#include <QDir>
#include <QQuickView>
#include <iostream>

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

    QString qmlPath = QCoreApplication::applicationDirPath() + "/../qml/qml/main.qml";

    QDir::setCurrent(QCoreApplication::applicationDirPath());

    QQuickView view;
    view.setSource(QUrl::fromLocalFile(qmlPath));
    view.show();

    return app.exec();
}
