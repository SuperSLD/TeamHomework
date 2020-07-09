#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include "mainwindow.h"

#include <QWidget>

/**
 * @brief The ContentWidget class
 *
 * Класс содержащий разметку одной части приложения.
 * Разделяет приложение на логически отделенные части.
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */
class ContentWidget : public QWidget
{
    Q_OBJECT
private:
    MainWindow *mainWindow;
public:
    ContentWidget(MainWindow *window, QWidget *parent = nullptr);
    ~ContentWidget();
    MainWindow* getMainWindow();
signals:

};

#endif // CONTENTWIDGET_H
