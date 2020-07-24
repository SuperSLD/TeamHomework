#include "loginwindow.h"
#include "property.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");

    LoginWindow w;
    return a.exec();
}
