#include "myhost.h"

MyHost::MyHost(QObject *parent)
    : QObject{parent}{
    host=new QTcpSocket(this);
    connect(host,&QTcpSocket::connected,this,&::MyHost::toUiConnected);
    connect(host,&QTcpSocket::disconnected,this,&::MyHost::toUiDisconneted);
    connect(host, &QTcpSocket::readyRead, this, [this]() {
        QByteArray data = host->readAll();
        emit toUiNewMessage(QString::fromUtf8(data));
    });
}
void MyHost::connectToServer(const QString &address, unsigned port){
    host->connectToHost(address, port);
}
void MyHost::disconnectFromServer(){
    host->disconnectFromHost();
}
void MyHost::sendMessage(const QString &messg){
    host->write(messg.toUtf8());//не понял почему ту стринг не рбаоет, write ждет имнно вектор char

}
