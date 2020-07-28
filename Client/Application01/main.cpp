#include "loginwindow.h"
#include "property.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
    QApplication a(argc, argv);

    LoginWindow w;
    return a.exec();
}
