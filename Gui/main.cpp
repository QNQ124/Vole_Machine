#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "vmachine.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Machine machine;

    engine.rootContext()->setContextProperty("machine", &machine);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Gui", "Main");

    return app.exec();
}
