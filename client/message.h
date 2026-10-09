#ifndef MESSAGE_H
#define MESSAGE_H
#include <QString>

struct Message {
    QString sender;//отправитель
    QString text;
    bool isMe;
};
#endif // MESSAGE_H
