#include "deskwidget.h"

#include <QVBoxLayout>
#include <QWebSocket>

DeskWidget::DeskWidget(QWebSocket *webSocket)
    : QWidget() {
    this->webSocket = webSocket;

    QVBoxLayout *ui = new QVBoxLayout;



    this->setLayout(ui);
}

DeskWidget::~DeskWidget() {
    delete webSocket;
}
