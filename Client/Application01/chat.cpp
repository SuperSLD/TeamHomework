#include "chat.h"

#include <QVBoxLayout>

ChatWidget::ChatWidget(QWebSocket *webSocket)
    : QWidget() {
    this->webSocket = webSocket;

    QVBoxLayout *ui = new QVBoxLayout;


    this->setLayout(ui);
}

ChatWidget::~ChatWidget() {

}
