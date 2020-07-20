#ifndef PROPERTY_H
#define PROPERTY_H
#include <string>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlTableModel>
class Property
{
 
public:
  Property();

  void put(QString name, QString value, QSqlQuery query);
  QString get(QString name, QSqlQuery query);

private:
  QSqlDatabase db;
};

#endif // PROPERTY_H
