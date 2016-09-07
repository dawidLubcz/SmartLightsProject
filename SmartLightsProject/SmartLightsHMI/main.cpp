#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <unistd.h>
#include "chmisignalhandler.h"
#include <QColor>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);

    CHMISignalHandler oHandler;
    oHandler.init();

    QObject::connect(window, SIGNAL(turnOnSignal()), &oHandler, SLOT(turnOnSlot()));
    QObject::connect(window, SIGNAL(turnOffSignal()), &oHandler, SLOT(turnOffSlot()));
    QObject::connect(window, SIGNAL(setColSignal(int)), &oHandler, SLOT(setColSlot(int)));
    QObject::connect(window, SIGNAL(setBrigSignal(int)), &oHandler, SLOT(setBrightSlot(int)));
    QObject::connect(window, SIGNAL(setWhiteSignal()), &oHandler, SLOT(setWhiteSlot()));
    QObject::connect(window, SIGNAL(setAutoDimming(int)), &oHandler, SLOT(setAutoDimming(int)));
    QObject::connect(window, SIGNAL(setMinimumLuxVal(int)), &oHandler, SLOT(setMinimumLuxVal(int)));
    
    return app.exec();
}

