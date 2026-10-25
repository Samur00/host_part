#ifndef MYHOST_H
#define MYHOST_H

#include <QObject>

class QTcpSocket;

class MyHost : public QObject {
    Q_OBJECT

public:
    explicit MyHost(QObject *parent = nullptr);

    bool isConnected() const;

    void connectToServer(const QString &address, unsigned port);
    void disconnectFromServer();
    void sendMessage(const QString &messg);

private:
    QTcpSocket *m_host{nullptr};

signals:
    void toUiConnected();
    void toUiDisconneted();
    void toUiNewMessage(const QString &message);
};

#endif // MYHOST_H