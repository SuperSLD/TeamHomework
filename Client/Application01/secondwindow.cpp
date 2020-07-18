#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QTime>

QString Name="Ivan";
QString Suname="Ivanov";
QString Mail="IvanIvanov@mail.ru";
bool person=false;

/**
 * @brief SecondWindow::SecondWindow
 * @param parent
 *
 * Создание окна главного меню. Выпонляется при успешной авторизации.
 *
 * @author Zinyukov Pavel (FlyForest962@yandex.ru)
 */
SecondWindow::SecondWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondWindow){

    ui->setupUi(this);
    QPixmap pix1(":/resc/resc/1.jpg");
    int w = ui->label_5->width();
    int h = ui->label_5->height();

    ui->label_5->setPixmap(pix1.scaled(w, h, Qt::KeepAspectRatio));
    ui->label_3->setText(Name);
    ui->label->setText(Suname);
    ui->label_2->setText(Mail);

    webSocket  = new QWebSocket();
    webSocket->open(QUrl(("ws://jutter.online/TeamServer/connection")));
    connect(webSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(webSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(onMessage(QString)));
}

SecondWindow::~SecondWindow(){
    delete ui;
    delete webSocket;
}

/**
 * @brief SecondWindow::on_pushButton_2_clicked
 *
 * Выполняется при нажатии кнопки Выход.
 *
 * @author Zinyukov Pavel (FlyForest962@yandex.ru)
 */

void SecondWindow::on_pushButton_2_clicked()
{
    QApplication::quit();
}

/**
 * @brief SecondWindow::on_pushButton_clicked
 *
 * Выполняется при нажатии кнопки Файлы.
 *
 * @author Zinyukov Pavel (FlyForest962@yandex.ru)
 */

void SecondWindow::on_pushButton_clicked()
{
    ui->label_6->setText("Здесь скоро появятся Файлы");
    ui->stackedWidget->setCurrentIndex(1);
}

/**
 * @brief SecondWindow::on_pushButton_4_clicked
 *
 * Выполняется при нажатии кнопки Сообщения.
 *
 * @author Zinyukov Pavel (FlyForest962@yandex.ru)
 */

void SecondWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

/**
 * @brief SecondWindow::on_pushButton_3_clicked
 *
 * Выполняется при нажатии кнопки Задачи.
 *
 * @author Zinyukov Pavel (FlyForest962@yandex.ru)
 */

void SecondWindow::on_pushButton_3_clicked()
{
    ui->label_7->setText("Здесь скоро появятся Задачи");
    ui->stackedWidget->setCurrentIndex(3);
}

/**
 * @brief SecondWindow::onConnected
 *
 * Выполняется при успешном подключении вебсокета.
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */
void SecondWindow::onConnected() {
    ui->stackedWidget->setCurrentIndex(2);
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

/**
 * @brief SecondWindow::on_pushButton_5_clicked
 *
 * Отправка сообщений в чат с указанием отправителя и время отправки.
 *
 * @author Zinyukov Pavel (FlyForest962@yandex.ru)
 */

void SecondWindow::on_pushButton_5_clicked()
{
    QString str3 = ui->lineEdit->text();
    if (str3=="")
    {

    }
    else
    {
        Chat *label1 = new Chat (this);
        Chat *label2 = new Chat (this);
        ui->verticalLayout->addWidget(label1);
        label1->setText(Suname+" "+Name+"   "+QTime::currentTime().toString("hh:mm"));
        ui->verticalLayout->addWidget(label2);
        label2->setText(str3);
        ui->lineEdit->clear();
        person = true;
    }
}
