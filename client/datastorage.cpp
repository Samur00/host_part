#include "datastorage.h"

DataStorage::DataStorage(QObject *parent)
    : QObject{parent}
{}

void DataStorage::addMessage(const Message &msg)
{
    m_messages.append(msg);
    emit messageAdded(msg);
}

int DataStorage::count() const
{
    return m_messages.size();
}

const Message& DataStorage::at(int index) const
{
    return m_messages.at(index);
}

const QList<Message>& DataStorage::messages() const
{
    return m_messages;
}