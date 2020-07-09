#include "mainwidget.h"

#include <qboxlayout.h>
#include <qlabel.h>

MainWidget::MainWidget(MainWindow *window, QWidget *parent)
    :ContentWidget(window, parent){

    QLabel *label = new QLabel("Main Widget");
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

MainWidget::~MainWidget() {
}
