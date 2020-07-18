#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include <QWebSocket>

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();

signals:
    void Mainwindow();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();

    void onConnected();
    void onMessage(QString message);

private:
    Ui::SecondWindow *ui;
    QWebSocket *webSocket;
};

#endif // SECONDWINDOW_H
