#ifndef CHATCONTROLLER
#define CHATCONTROLLER

#include <QObject>
#include "messagemodel.h"
#include "myhost.h"
#include "datastorage.h"
class ChatController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isConnected READ isConnected NOTIFY connectionChanged)
    Q_PROPERTY(MessageModel* messageModel READ messageModel CONSTANT)

public:
    explicit ChatController(QObject *parent = nullptr);

    bool isConnected() const;
    MessageModel* messageModel();

    Q_INVOKABLE void connectToServer(const QString &address, unsigned port);
    Q_INVOKABLE void disconnectFromServer();
    Q_INVOKABLE void sendMessage(const QString &text);

signals:
    void connectionChanged();

private slots:
    void onNetworkConnected();
    void onNetworkDisconnected();
    void onNetworkMessageReceived(const QString &message);

private:
    MyHost m_host;
    DataStorage m_storage;
    MessageModel m_model;
};

#endif // CHATCONTROLLER
