#include "mainwindow.h"
#include "property.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QString test;
    Property property;
    property.put("egor","17");
    test = property.get("egor");
    qDebug() << test;
    return a.exec();
}
