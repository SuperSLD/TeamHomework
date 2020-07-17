#include "secondwindow.h"
#include "ui_secondwindow.h"

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
    ui->label_4->setText("Здесь скоро появятся Файлы");
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
    ui->label_4->setText("Здесь скоро появятся Сообщения");
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
    ui->label_4->setText("Здесь скоро появятся Задачи");
}
