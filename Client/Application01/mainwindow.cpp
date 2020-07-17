#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secondwindow.h"
#include "httprequest.h"
#include <QMessageBox>
#include "property.h"

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

void MainWindow::on_pushButton_2_clicked()
{
   QApplication::quit();
}

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
