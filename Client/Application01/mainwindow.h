#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "secondwindow.h"

#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void resizeEvent(QResizeEvent *event);

private slots:



    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    // Обработчик данных полученных от объекта QNetworkAccessManager
    void onResult(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    SecondWindow *secwindow;

    QNetworkAccessManager *networkManager;

};
#endif // MAINWINDOW_H
