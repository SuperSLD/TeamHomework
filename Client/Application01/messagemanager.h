#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include "messagemodel.h"

#include <QSqlDatabase>
#include <QLinkedList>


/**
 * @brief The MessageManager class
 *
 * Класс для обработки и сохранения сообщений.
 *
 * @author Leonid Solyanoy (solyanoy.leonid@gmail.com)
 */
class MessageManager {
private:
    QSqlDatabase db;
    MessageManager *mm = nullptr;
    QLinkedList<MessageModel*> messages;
protected:
public:
    MessageManager();
    ~MessageManager();

    void addMessage(QString type,
                    QString text,
                    QString author,
                    QString time);
    QLinkedList<MessageModel*> getLastMessages();
};

#endif // MESSAGEMANAGER_H
