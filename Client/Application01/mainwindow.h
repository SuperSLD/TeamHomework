#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebSocket>
#include "chat.h"

#include <QJsonObject>
#include <QSettings>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
    void addMessage(QString message, QString time, QString author);

signals:
    void LoginWindow();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();

    void onConnected();
    void onMessage(QString message);
    void onDisconnected();

    void on_pushButton_5_clicked();

    void keyPressEvent(QKeyEvent *event);

private:
    QWebSocket *webSocket;
    QSettings *settings;

    QJsonObject m_currentJsonObject;

};

#endif // MAINWINDOW_H
