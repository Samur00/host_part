#include "myhost.h"

MyHost::MyHost(QObject *parent)
    : QObject{parent}{
    m_host=new QTcpSocket(this);
    connect(m_host,&QTcpSocket::connected,this,&::MyHost::toUiConnected);
    connect(m_host,&QTcpSocket::disconnected,this,&::MyHost::toUiDisconneted);
    connect(m_host, &QTcpSocket::readyRead, this, [this]() {
        QByteArray data = m_host->readAll();
        emit toUiNewMessage(QString::fromUtf8(data));
    });
}
void MyHost::connectToServer(const QString &address, unsigned port){
    m_host->connectToHost(address, port);
}
void MyHost::disconnectFromServer(){
    m_host->disconnectFromHost();
}
void MyHost::sendMessage(const QString &messg){
    m_host->write(messg.toUtf8());//не понял почему ту стринг не рбаоет, write ждет имнно вектор char

}
