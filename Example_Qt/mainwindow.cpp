#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Изображение 1
    QPixmap pix(":/resours/img/img_1280x720.jpg");
    int w = ui->image->width();
    int h = ui->image->height();

    ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

    //Изображение 2
    QPixmap pix_2(":/resours/img/img_361x300.jpg");
    int w_2 = ui->image_2->width();
    int h_2 = ui->image_2->height();

    ui->image_2->setPixmap(pix_2.scaled(w, h, Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Клик на кнопку
void MainWindow::on_pushButton_clicked()
{
    QString login = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    if (login == "tambovnikita@yandex.ru" && password == "12345")
    {
        QMessageBox::information(this, "Результат авторизации", "Авторизация успешно пройдена!");
    }
    else
    {
        QMessageBox::warning(this, "Результат авторизации", "Авторизация не пройдена!");
    }
}
