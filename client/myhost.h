#ifndef MYHOST_H
#define MYHOST_H

#include <QObject>
#include <qqmlregistration.h>

class QTcpSocket;

class MyHost : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool isConnected READ isConnected NOTIFY connectionChanged)

public:
    explicit MyHost(QObject *parent = nullptr);

    bool isConnected() const;

    Q_INVOKABLE void connectToServer(const QString &adpress, unsigned port);
    Q_INVOKABLE void disconnectFromServer();
    Q_INVOKABLE void sendMessage(const QString &messg);

private:
    QTcpSocket *m_host{nullptr};

signals:
    void connectionChanged();
    void toUiConnected();
    void toUiDisconneted();
    void toUiNewMessage(const QString &message);
    void messageSent(const QString &messg);

private slots:
};

#endif // MYHOST_H