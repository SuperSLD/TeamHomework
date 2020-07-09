#include "contentwidget.h"

ContentWidget::ContentWidget(MainWindow *window, QWidget *parent) : QWidget(parent) {
    this->mainWindow = window;
}

ContentWidget::~ContentWidget() {
    delete this->mainWindow;
}

MainWindow* ContentWidget::getMainWindow() {
    return this->mainWindow;
}
