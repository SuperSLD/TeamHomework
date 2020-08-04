#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include <QString>


/**
 * @brief The MessageModel class
 *
 * Модель хранения и обработки данных связанных
 * с сообщениями.
 *
 * @author Solyanoy Leonid (solyanoy.leonid@gmail.com)
 */
class MessageModel {
private:
    QString type;
    QString time;
    QString author;
    QString content;
protected:
public:
    MessageModel(QString type,
                 QString time,
                 QString author,
                 QString content);
    ~MessageModel();

    QString getType();
    QString getTime();
    QString getAuthor();
    QString getContent();
};

#endif // MESSAGEMODEL_H
