#include "chatcontroller.h"

ChatController::ChatController(QObject *parent)
    : QObject{parent}
{
    connect(&m_host, &MyHost::toUiConnected, this, &ChatController::onNetworkConnected);
    connect(&m_host, &MyHost::toUiDisconneted, this, &ChatController::onNetworkDisconnected);
    connect(&m_host, &MyHost::toUiNewMessage, this, &ChatController::onNetworkMessageReceived);

    connect(&m_host, &MyHost::toUiConnected, this, &ChatController::connectionChanged);
    connect(&m_host, &MyHost::toUiDisconneted, this, &ChatController::connectionChanged);
}
bool ChatController::isConnected() const
{
    return m_host.isConnected();
}

MessageModel* ChatController::messageModel()
{
    return &m_model;
}

void ChatController::connectToServer(const QString &address, unsigned port)
{
    m_host.connectToServer(address, port);
}

void ChatController::disconnectFromServer()
{
    m_host.disconnectFromServer();
}

void ChatController::sendMessage(const QString &text)
{
    if (text.trimmed().isEmpty())
        return;

    m_host.sendMessage(text);
    m_storage.addMessage({"Я", text, true});
}

void ChatController::onNetworkConnected()
{
    m_storage.addMessage({"Система", "Подключено к серверу!", false});
}

void ChatController::onNetworkDisconnected()
{
    m_storage.addMessage({"Система", "Соединение разорвано.", false});
}

void ChatController::onNetworkMessageReceived(const QString &message)
{
    m_storage.addMessage({"Собеседник", message, false});
}