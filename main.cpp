#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <client/myhost.h>
int main(int argc, char *argv[])
{
    qputenv("QT_QUICK_CONTROLS_STYLE", "Material");
    qputenv("QT_QUICK_CONTROLS_MATERIAL_ACCENT", "Teal");
    //qputenv("QT_QUICK_CONTROLS_MATERIAL_THEME", "Dark");
    QGuiApplication app(argc, argv);
    /*
    MyHost* client = new MyHost(&app);
    QObject::connect(client, &MyHost::toUiNewMessage, [](const QString &message) {
        qDebug() << "--> [CLIENT] Получено от сервера:" << message;
    });

    QObject::connect(client, &MyHost::toUiConnected, [&client]() {
        qDebug() << "--> [CLIENT] Успешно подключились! Отправляем ответ...";
        client->sendMessage("Привет с клиента!");
    });

    client->connectToServer("localhost", 11111);
    */
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
