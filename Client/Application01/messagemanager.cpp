#include "messagemanager.h"

#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QLinkedList>

/**
 * @brief MessageManager::MessageManager
 *
 * Конструктор без параметров.
 * Подключение локальной базы.
 *
 * @author Solyanoy Leonid (solyanoy.leonid@gmail.com)
 */
MessageManager::MessageManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("userData.db");
    db.open();
    QSqlQuery query(db);
    query.exec("CREATE TABLE \"messages\" ("
                  "\"id\"	INTEGER NOT NULL UNIQUE,"
                  "\"text_message\"	TEXT NOT NULL,"
                  "\"type_message\"	TEXT NOT NULL,"
                  "\"time_message\"	TEXT NOT NULL,"
                  "\"author\"	TEXT NOT NULL,"
                  "PRIMARY KEY(\"id\" AUTOINCREMENT)"
               ");");
}

MessageManager::~MessageManager() {
    delete &db;
    delete mm;
    delete &messages;
}

/**
 * @brief MessageManager::addMessage
 *
 * Добавление сообщения в бд.
 *
 * @param type тип сообщения.
 * @param text текст сообщения
 * @param author автор сообщения.
 * @param time время отправки.
 *
 * @author Solyanoy Leonid (solyanoy.leonid@gmail.com)
 */
void MessageManager::addMessage(QString type,
                           QString text,
                           QString author,
                           QString time) {
    MessageModel *messageModel = new MessageModel(type, time, author, text);
    this->messages.append(messageModel);

    QSqlQuery query(db);
    query.exec("INSERT INTO messages (text_message, type_message, time_message, author) "
               "VALUES ('"+text+"', '"+type+"','"+time+"', '"+author+"')");
}

/**
 * @brief MessageManager::getLastMessages
 *
 * Получение списка последних сообщений,
 * сохраненный в локальную бд.
 *
 * @return список объектов @class MessageModel;
 *
 * @author Solyanoy Leonid (solyanoy.leonid@gmail.com)
 */
QLinkedList<MessageModel*> MessageManager::getLastMessages() {
    QSqlQuery query(db);
    query.exec("SELECT id, text_message, type_message, time_message, author "
               "FROM messages");
    while (query.next()) {
        MessageModel *messageModel = new MessageModel(query.value(2).toString(),
                                                     query.value(3).toString(),
                                                     query.value(4).toString(),
                                                     query.value(1).toString());
        this->messages.append(messageModel);
    }
    return this->messages;
}


