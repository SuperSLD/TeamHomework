#include "secondwindow.h"
#include "ui_secondwindow.h"

SecondWindow::SecondWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
    QPixmap pix1(":/resc/resc/1.jpg");
    int w = ui->label_5->width();
    int h = ui->label_5->height();

    ui->label_5->setPixmap(pix1.scaled(w, h, Qt::KeepAspectRatio));
}

SecondWindow::~SecondWindow()
{
    delete ui;
}

void SecondWindow::on_pushButton_2_clicked()
{
    QApplication::quit();
}

void SecondWindow::on_pushButton_clicked()
{
    ui->label_4->setText("Здесь скоро появятся Файлы");
}

void SecondWindow::on_pushButton_4_clicked()
{
    ui->label_4->setText("Здесь скоро появятся Сообщения");
}

void SecondWindow::on_pushButton_3_clicked()
{
    ui->label_4->setText("Здесь скоро появятся Задачи");
}
