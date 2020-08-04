#include "messagemodel.h"

/**
 * @brief MessageModel::MessageModel
 *
 * Инициализация значений.
 *
 * @author Solyanoy Leonid (solyanoy.leonid@gmail.com)
 */
MessageModel::MessageModel(QString type,
                           QString time,
                           QString author,
                           QString content){
    this->time = time;
    this->type = type;
    this->author = author;
    this->content = content;
}


MessageModel::~MessageModel() {
    delete &time;
    delete &type;
    delete &author;
    delete &content;
}

QString MessageModel::getTime() {
    return this->time;
}

QString MessageModel::getType() {
    return this->type;
}

QString MessageModel::getAuthor() {
    return this->author;
}

QString MessageModel::getContent() {
    return this->content;
}
