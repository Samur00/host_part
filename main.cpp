#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <client/myhost.h>
#include "datastorage.h"
#include "messagemodel.h"

int main(int argc, char *argv[])
{
    qputenv("QT_QUICK_CONTROLS_STYLE", "Material");
    qputenv("QT_QUICK_CONTROLS_MATERIAL_ACCENT", "Teal");
    //qputenv("QT_QUICK_CONTROLS_MATERIAL_THEME", "Dark");
    QGuiApplication app(argc, argv);

    MyHost host;
    DataStorage storage;
    MessageModel chatModel(&storage);

    QObject::connect(&host, &MyHost::toUiNewMessage, &storage, [&storage](const QString &text) {
        storage.addMessage({"Сервер", text, false});
    });

    QObject::connect(&host, &MyHost::messageSent, &storage, [&storage](const QString &text) {
        storage.addMessage({"Я", text, true});
    });

    QObject::connect(&host, &MyHost::toUiConnected, &storage, [&storage]() {
        storage.addMessage({"Система", "Подключено к серверу!", false});
    });

    QObject::connect(&host, &MyHost::toUiDisconneted, &storage, [&storage]() {
        storage.addMessage({"Система", "Соединение разорвано.", false});
    });

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("host", &host);
    engine.rootContext()->setContextProperty("chatModel", &chatModel);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("host", "Main");

    return app.exec();
}