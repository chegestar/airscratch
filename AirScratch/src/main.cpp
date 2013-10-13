#include <QtGui/QGuiApplication>

#include <QQmlContext>
#include <QtQml>

#include "qtquick2applicationviewer.h"

#include "scratchcontroller.h"
#include "audiograph.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    ScratchController* sc = new ScratchController(&app);

    qmlRegisterType<AudioGraph>("com.sandst1.components", 1, 0, "AudioGraph");

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/AirScratch/main.qml"));
    viewer.showExpanded();

    viewer.rootContext()->setContextProperty("ScratchCtrl", sc);

    return app.exec();
}

