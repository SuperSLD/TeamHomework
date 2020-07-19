#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "property.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QTime>
#include <QtGui>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QSettings>

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

    settings = new QSettings("settings.ini", QSettings::IniFormat);
    ui->label_5->setPixmap(pix1.scaled(w, h, Qt::KeepAspectRatio));
    ui->label_3->setText(settings->value("name", "default").toString());
    ui->label->setText(settings->value("lastname", "default").toString());
    ui->label_2->setText(settings->value("email", "default").toString());

    webSocket  = new QWebSocket();
    webSocket->open(QUrl(("ws://jutter.online/TeamServer/connection")));
    //webSocket->open(QUrl(("ws://localhost:8080/TeamServer/connection")));
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
    QJsonObject textObject;
    textObject["id"] = settings->value("id").toString();
    textObject["key"] = settings->value("password").toString();
    textObject["type"] = "connect_user";

    QJsonDocument doc(textObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    webSocket->sendTextMessage(strJson);
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
    } else if (messasgeType == "group_message") {
        //обработка сообщения группового чата.
        addMessage(obj["message"].toString(),
                   obj["time"].toString(),
                   obj["author"].toString());
    }

}

/**
 * @brief SecondWindow::on_pushButton_5_clicked
 *
 * Отправка сообщений в чат с указанием отправителя и время отправки.
 *
 * @author Zinyukov Pavel (FlyForest962@yandex.ru) (Пустая функция.)
 * @author Nikita Tambov (tambovnikita@yandex.ru) (Преобразование сообщений в JSON.)
 */

void SecondWindow::on_pushButton_5_clicked() {
    QString message = ui->lineEdit->text();

    if (message==""){

    } else {
        // Создаём объект текста
        QJsonObject textObject;
        textObject["message"] = ui->lineEdit->text();  // Устанавливаем message
        textObject["author"] = (settings->value("name", "default").toString()
                                + " " + settings->value("lastname", "default").toString());  // Устанавливаем author
        textObject["type"] = "group_message";  // Устанавливаем type
        textObject["message_type"] = "simple_message";  // Устанавливаем message_type

        QJsonDocument doc(textObject);
        QString strJson(doc.toJson(QJsonDocument::Compact));
        webSocket->sendTextMessage(strJson);
    }
}


/**
 * @brief SecondWindow::addMessage
 * @param message текст сообщения.
 * @param time время отправки (а не время получения).
 * @param author автор сообщения.
 * 
 * Вставка сообщения в чат.
 * 
 * @author Zinyukov Pavel (FlyForest962@yandex.ru) (написал весь код)
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com) (обернул в функцию) 
 */
 void SecondWindow::addMessage(QString message, QString time, QString author) {
    if (message==""){

    } else {
        Chat *label1 = new Chat (this);
        Chat *label2 = new Chat (this);
        ui->verticalLayout->addWidget(label1);
        QString authorColor = "white";
        if (author == (settings->value("name", "default").toString()
                       + " " + settings->value("lastname", "default").toString())) {
            authorColor = "#87FFD5";
        }
        label1->setText("<html><head/><body><p><span style=\" color:"+authorColor+";"
                        " font-family:arial;\">"+author+"</span><span style=\" "
                        "color:#808080; font-family:arial;\"> "+time+"</span></p></body></html>");
        ui->verticalLayout->addWidget(label2);
        label2->setText(message);
        ui->lineEdit->clear();
        person = true;
    }
}

/**
 * @brief SecondWindow::keyPressEvent
 * @param event
 *
 * Отправка сообщения в чат с помощью кнопки Enter.
 *
 * @author Zinyukov Pavel (FlyForest962@yandex.ru)
 * @author Nikita Tambov (tambovnikita@yandex.ru) (Преобразование сообщений в JSON.)
 */

void SecondWindow::keyPressEvent(QKeyEvent *event)
    {
        if (event->key()==Qt::Key_Enter || event->key() == Qt::Key_Return)
        {
            QString str3 = ui->lineEdit->text();
            if (str3=="")
            {

            }
            else
            {
                QJsonObject textObject;
                textObject["message"] = ui->lineEdit->text();  // Устанавливаем message
                textObject["author"] = (settings->value("name", "default").toString()
                                        + " " + settings->value("lastname", "default").toString());  // Устанавливаем author
                textObject["type"] = "group_message";  // Устанавливаем type
                textObject["message_type"] = "simple_message";  // Устанавливаем message_type

                QJsonDocument doc(textObject);
                QString strJson(doc.toJson(QJsonDocument::Compact));
                webSocket->sendTextMessage(strJson);
            }
        }
    }
