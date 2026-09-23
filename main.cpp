#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <client/myhost.h>
int main(int argc, char *argv[])
{
    qputenv("QT_QUICK_CONTROLS_STYLE", "Material");
    qputenv("QT_QUICK_CONTROLS_MATERIAL_ACCENT", "Teal");
    //qputenv("QT_QUICK_CONTROLS_MATERIAL_THEME", "Dark");
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("host", "Main");

    return app.exec();
}
