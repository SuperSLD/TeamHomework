#include "secondwindow.h"
#include "ui_secondwindow.h"

#include <QJsonDocument>
#include <QJsonObject>

SecondWindow::SecondWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondWindow){

    ui->setupUi(this);
    QPixmap pix1(":/resc/resc/1.jpg");
    int w = ui->label_5->width();
    int h = ui->label_5->height();

    ui->label_5->setPixmap(pix1.scaled(w, h, Qt::KeepAspectRatio));

    webSocket  = new QWebSocket();
    webSocket->open(QUrl(("ws://jutter.online/TeamServer/connection")));
    connect(webSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(webSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(onMessage(QString)));
}

SecondWindow::~SecondWindow(){
    delete ui;
    delete webSocket;
}

void SecondWindow::on_pushButton_clicked(){
    ui->label_4->setText("Здесь скоро появятся Файлы");
}

void SecondWindow::on_pushButton_4_clicked(){
    ui->label_4->setText("Здесь скоро появятся Сообщения");
}

void SecondWindow::on_pushButton_3_clicked(){
    ui->label_4->setText("Здесь скоро появятся Задачи");
}

/**
 * @brief SecondWindow::onConnected
 *
 * Выполняется при успешном подключении вебсокета.
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */
void SecondWindow::onConnected() {
    ui->label_4->setText("WebSocket подключен");
}

/**
 * @brief SecondWindow::onMessage
 * @param string входяшее сообщение
 *
 * Обработка входящих сообщений.
 * Каждое сообщение имеет type в зависимости от
 * которого их необходимо обрабатывать разным способом.
 *
 * отправка обратных сообщений:
 * webSocket->sendTextMessage("Hello From Qt!!!");
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */
void SecondWindow::onMessage(QString string) {
    //создаем JSON object из строки.
    QJsonDocument doc = QJsonDocument::fromJson(string.toUtf8());
    QJsonObject obj;
    if(!doc.isNull()) {
        if(doc.isObject()) {
            obj = doc.object();
        }
        else {
            qDebug() << "Document is not an object" << endl;
        }
    } else {
        qDebug() << "Invalid JSON...\n" << string << endl;
    }

    QString messasgeType = obj["type"].toString();

    if (messasgeType == "ping") {
        //обработка тестового пинг сообщения.
        qDebug() << "WebSocket подключен\nколичество пинг сообщений:"
                             + obj["count"].toString() + "\nсообщение: " + obj["message"].toString() << endl;
    } else if (messasgeType == "group_message") {
        //обработка сообщения группового чата.
    }

}
