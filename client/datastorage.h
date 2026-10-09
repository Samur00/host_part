#ifndef DATASTORAGE_H
#define DATASTORAGE_H
#include <QList>
#include "message.h"
#include <QObject>

class DataStorage : public QObject
{
    Q_OBJECT
public:
    explicit DataStorage(QObject *parent = nullptr);
    void addMessage(const Message &msg);
    int count() const;
    const Message& at(int index) const;
    const QList<Message>& messages() const;

signals:
    void messageAdded(const Message &msg);

private:
    QList<Message> m_messages;
};

#endif // DATASTORAGE_H

