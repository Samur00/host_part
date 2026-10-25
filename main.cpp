#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "chatcontroller.h"
int main(int argc, char *argv[])
{
    qputenv("QT_QUICK_CONTROLS_STYLE", "Material");
    qputenv("QT_QUICK_CONTROLS_MATERIAL_ACCENT", "Teal");
    //qputenv("QT_QUICK_CONTROLS_MATERIAL_THEME", "Dark");
    QGuiApplication app(argc, argv);

    ChatController chatController;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("chatController", &chatController);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("host", "Main");

    return app.exec();
}