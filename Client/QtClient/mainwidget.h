#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "contentwidget.h"



class MainWidget : public ContentWidget
{
public:
    MainWidget(MainWindow *window, QWidget *parent = nullptr);
    ~MainWidget();
};

#endif // MAINWIDGET_H
