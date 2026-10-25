#include "myhost.h"
#include <QTcpSocket>

MyHost::MyHost(QObject *parent)
    : QObject{parent}
{
    m_host = new QTcpSocket(this);

    connect(m_host, &QTcpSocket::connected, this, &MyHost::toUiConnected);
    connect(m_host, &QTcpSocket::disconnected, this, &MyHost::toUiDisconneted);

    connect(m_host, &QTcpSocket::readyRead, this, [this]() {
        QByteArray data = m_host->readAll();
        emit toUiNewMessage(QString::fromUtf8(data));
    });
}

bool MyHost::isConnected() const
{
    return m_host && m_host->state() == QAbstractSocket::ConnectedState;
}

void MyHost::connectToServer(const QString &address, unsigned port)
{
    m_host->connectToHost(address, port);
}

void MyHost::disconnectFromServer()
{
    m_host->disconnectFromHost();
}

void MyHost::sendMessage(const QString &messg)
{
    if (isConnected()) {
        m_host->write(messg.toUtf8());
    }
}