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
  db.open();
  if( !query.exec(
                  "CREATE TABLE Settings("
                  "   Name VARCHAR( 200 ) NOT NULL,"
                  "   Value VARCHAR( 200 ) NOT NULL"
                  ")"
      ) ) {
          qDebug() << db.lastError().text();
      }

  qDebug() << db.open(); //true - если БД открылась
}

void Property::put(QString name, QString value){
   QSqlQuery query;
  query.prepare("INSERT INTO Settings( Name, Value ) "
                "VALUES( ?, ? )");

  query.addBindValue( name );
  query.addBindValue( value );
  if( !query.exec() ) {
          qDebug() << db.lastError().text();
      }

}

QString Property::get(QString name ){
  QSqlQuery query;
  if( !query.exec( "SELECT * FROM Settings" ) ) {
          qDebug() << db.lastError().text();
  }
 
  query.prepare("SELECT value FROM Settings WHERE Name LIKE ?");
  query.addBindValue( name );
  query.exec();
  query.first();
  return query.value(0).toString();
}

Property:: ~Property() {
}
