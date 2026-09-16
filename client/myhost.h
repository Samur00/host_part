#ifndef MYHOST_H
#define MYHOST_H

#include <QObject>
#include <QTcpSocket>
//#include <QtQml/qqmlregistration.h>???
#include <qqmlregistration.h>
class MyHost : public QObject{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit MyHost(QObject *parent = nullptr);
    Q_INVOKABLE void connectToServer(const QString &adpress, unsigned port);
    Q_INVOKABLE void disconnectFromServer();
    Q_INVOKABLE void sendMessage(const QString &messg);
private:
    QTcpSocket *host;//мб нужна инициализация базоавя
signals:
    void toUiConnected();
    void toUiDisconneted();
    void toUiNewMessage(const QString &message);
private slots://не понял почему можно на сигнал вызвать сигнал
};

#endif // MYHOST_H
