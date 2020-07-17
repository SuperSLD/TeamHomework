#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secondwindow.h"
#include "httprequest.h"
#include <QMessageBox>
#include <QPixmap>
#include <QPalette>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
