#include "messagemodel.h"

MessageModel::MessageModel(DataStorage *storage, QObject *parent)
    : QAbstractListModel(parent), m_storage(storage)
{
    if (m_storage) {
        connect(m_storage, &DataStorage::messageAdded, this, &MessageModel::onMessageAdded);
    }
}

int MessageModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !m_storage)
        return 0;
    return m_storage->count();
}

QVariant MessageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !m_storage || index.row() < 0 || index.row() >= m_storage->count())
        return QVariant();

    const Message &msg = m_storage->at(index.row());
    switch (role) {
    case SenderRole:
        return msg.sender;
    case TextRole:
        return msg.text;
    case IsMeRole:
        return msg.isMe;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> MessageModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[SenderRole] = "sender";
    roles[TextRole]   = "text";
    roles[IsMeRole]   = "isMe";
    return roles;
}

void MessageModel::onMessageAdded(const Message &)
{
    if (!m_storage)
        return;

    int newRow = m_storage->count() - 1;
    beginInsertRows(QModelIndex(), newRow, newRow);
    endInsertRows();
}