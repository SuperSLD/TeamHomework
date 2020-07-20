#include "property.h"
#include <QString>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlTableModel>
Property::Property()
{
  db = QSqlDatabase::addDatabase( "QSQLITE" );
  db.setDatabaseName( "DataBase" );
  QSqlQuery query( db );
  if( !query.exec(
                  "CREATE TABLE Settings("
                  "   Name VARCHAR( 200 ) NOT NULL,"
                  "   Value VARCHAR( 200 ) NOT NULL"
                  ")"
      ) ) {
          qDebug() << db.lastError().text();
      }
}

void Property::put(QString name, QString value, QSqlQuery query){
  //put(имя строки, значение строки, тут всегда писать query)
  query.prepare("INSERT INTO Settings( Name, Value ) "
                "VALUES( ?, ? )");

  query.addBindValue( name );
  query.addBindValue( value );
  if( !query.exec() ) {
          qDebug() << db.lastError().text();
      }
}
QString Property::get(QString name, QSqlQuery query)
//get(имя строки, тут всегда писать query)
{
  if( !query.exec( "SELECT * FROM Settings" ) ) {
          qDebug() << db.lastError().text();
      }
  query.exec("SELECT * FROM Settings WHERE Name LIKE name");
  query.first();
  QString val = query.value(0).toString();
  return val;
}
