#ifndef PROPERTY_H
#define PROPERTY_H
#include <string>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlTableModel>
/**
 * @brief The Property class
 *
 * Класс создания БД с функциями внесения данных put и поиска get.
 * 
 * @author Skok Vyacheslav(pthfnd@mail.ru)
 * @author Kuklin Egor(kuklin_99@bk.ru)
 */
class Property
{
 
public:
   Property();
   ~Property();

  void put(QString name, QString value);
  QString get(QString name);

private:
  QSqlDatabase db;
};

#endif // PROPERTY_H
