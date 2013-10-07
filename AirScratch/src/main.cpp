#include <QtGui/QGuiApplication>

#include <QQmlContext>

#include "qtquick2applicationviewer.h"

#include "scratchcontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    ScratchController* sc = new ScratchController(&app);

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/AirScratch/main.qml"));
    viewer.showExpanded();


    viewer.rootContext()->setContextProperty("ScratchCtrl", sc);

    return app.exec();
}

