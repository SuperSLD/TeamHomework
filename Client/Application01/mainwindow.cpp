#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secondwindow.h"
#include "httprequest.h"
#include <QMessageBox>
#include <QPixmap>
#include <QPalette>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    networkManager = new QNetworkAccessManager();
    // Подключаем networkManager к обработчику ответа
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onResult);
    // Получаем данные, а именно JSON файл с сайта по определённому url
    networkManager->get(QNetworkRequest(QUrl("http://jutter.online/TeamServer/auth?email=solyanoy.leonid@gmail.com&password=299792458")));

}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::resizeEvent
 * @param event
 *
 * Установка фонового изображения на окно авторизации.
 *
 * @author Zinyukov Pavel (FlyForest962@yandex.ru)
 */

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QPixmap bkgnd(":/resc/resc/back_login.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    QMainWindow::resizeEvent(event);
}

/**
 * @brief MainWindow::on_pushButton_2_clicked
 *
 * Выполняется при нажатии кнопки Выход.
 *
 * @author Zinyukov Pavel (FlyForest962@yandex.ru)
 */

void MainWindow::on_pushButton_2_clicked()
{
   QApplication::quit();}

/**
 * @brief MainWindow::on_pushButton_clicked
 *
 * Выполняется при нажатии кнопки Вход.
 *
 * @author Zinyukov Pavel (FlyForest962@yandex.ru)
 */

void MainWindow::on_pushButton_clicked()
{
    QString login = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    //HTTPRequest *req = new HTTPRequest("jutter.online", 1000);
    //std::string resp = req->get("auth?email="+login.toStdString()+"&password="+password.toStdString());


    if ((login=="user1" && password=="test") || (login=="user2" && password=="happy"))
     {
        hide();
        secwindow = new SecondWindow();
        connect(secwindow, &SecondWindow::Mainwindow,this, &MainWindow::show);
        secwindow->show();
        this->close();
    }
    else
    {
      QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль!");
    }
}


void Widget::onResult(QNetworkReply *reply)
{
    // Если ошибки отсутсвуют
    if(!reply->error()){

        // То создаём объект Json Document, считав в него все данные из ответа
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());

        // Забираем из документа корневой объект
        QJsonObject root = document.object();
        /* Находим объект "errcode", который располагается самым первым в корневом объекте.
         * С помощью метода keys() получаем список всех объектов и по первому индексу
         * забираем название объекта, по которому получим его значение
         * */
        ui->lineEdit->setText(root.keys().at(0) + ": " + root.value(root.keys().at(0)).toString());

        /*

        // Второе значение пропишем строкой
        QJsonValue jv = root.value("password");

        // Если значение является массивом, ...
        if(jv.isArray()){
            // ... то забираем массив из данного свойства
            QJsonArray ja = jv.toArray();
            // Перебирая все элементы массива ...
            for(int i = 0; i < ja.count(); i++){
                QJsonObject subtree = ja.at(i).toObject();
                // Забираем значения свойств имени и фамилии добавляя их в textEdit
                ui->textEdit->append(subtree.value("firstName").toString() +
                                     " " +
                                     subtree.value("lastName").toString());
            }
        }
        // В конце забираем lastname и также выводим в textEdit
        ui->textEdit->append(QString::number(root.value("lastnamer").toInt()));

        */
    }
    reply->deleteLater();
}
