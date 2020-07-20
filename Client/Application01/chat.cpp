#include "chat.h"
#include "ui_chat.h"

Chat::Chat(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
}

Chat::~Chat()
{
    delete ui;
}
