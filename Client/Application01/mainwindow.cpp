#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secondwindow.h"
#include "httprequest.h"
#include <QMessageBox>
#include "property.h"

#include <QPixmap>
#include <QPalette>
#include <QSettings>

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
    QSettings *settings = new QSettings("settings.ini", QSettings::IniFormat);
    if (settings->value("email", "").toString().length() > 4) {
        openMainWindow();
        return;
    }

    ui->setupUi(this);

    this->show();
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
    QString email = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    networkManager = new QNetworkAccessManager();
    // Подключаем networkManager к обработчику ответа
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onResult);
    // Получаем данные, а именно JSON файл с сайта по определённому url
    networkManager->get(
                QNetworkRequest(QUrl(
            "http://jutter.online/TeamServer/auth?email="+email+"&password="+password
                                    )
                )
    );
}

/**
 * @brief MainWindow::onResult
 * @param reply ответ сервера.
 *
 * Обработка ответа с данными пользователя и их проверка.
 *
 * @author Nikita Tambov (tambovnikita@yandex.ru)
 * @author Solyanoy Leonid (solyanoy.leonid@gmail.com)
 */
void MainWindow::onResult(QNetworkReply *reply)
{
    // Если ошибки отсутсвуют
    if(!reply->error()){
        QString email = ui->lineEdit->text();
        QString password = ui->lineEdit_2->text();

        // То создаём объект Json Document, считав в него все данные из ответа
        QByteArray resp = reply->readAll();
        qDebug() << resp << endl;
        QJsonDocument doc = QJsonDocument::fromJson(resp);
        QJsonObject obj;
        if(!doc.isNull()) {
            if(doc.isObject()) {
                obj = doc.object();
                qDebug() << obj["email"].toString() << endl;
            }
            else {
                qDebug() << "Document is not an object" << endl;
            }
        } else {
            qDebug() << "Invalid JSON...\n" << endl;
        }
        if (obj["errcode"].toString() == "0") {
            //сохранение данных.
            QSettings *settings = new QSettings("settings.ini", QSettings::IniFormat);
            settings->setValue("name", obj["name"].toString());
            settings->setValue("lastname", obj["lastname"].toString());
            settings->setValue("password", obj["password"].toString());
            settings->setValue("email", obj["email"].toString());
            settings->setValue("id", obj["id"].toString());
            settings->sync(); //записываем настройки

            //переход к следующему окну.
            openMainWindow();
        } else if (obj["errcode"].toString() == "1"){
            QMessageBox::warning(this, "Ошибка", "Почта не найдена!");
        } else if (obj["errcode"].toString() == "2"){
            QMessageBox::warning(this, "Ошибка", "Неверный пароль!");
        } else if (obj["errcode"].toString() == "3"){
            QMessageBox::warning(this, "Ошибка", "Произошла неизвестная ошибка на сервере!");
        }
    }
    reply->deleteLater();
}

/**
 * @brief MainWindow::openMainWindow
 *
 * Переход к главному окну приложения.
 *
 * @author Solyanoy Leonid (solyanoy.leonid@gmail.com)
 */
void MainWindow::openMainWindow() {
    hide();
    secwindow = new SecondWindow();
    connect(secwindow, &SecondWindow::Mainwindow,this, &MainWindow::show);
    secwindow->show();
    this->close();
}
