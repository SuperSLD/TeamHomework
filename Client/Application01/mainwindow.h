#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebSocket>
#include "chatwidget.h"
#include "deskwidget.h"

#include <QJsonObject>
#include <QSettings>
#include <QStackedWidget>


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
    void exitButtonClicked();

    void chatButtonClicked();
    void deskButtonClicked();
    void filesButtonClicked();

    void onConnected();
    void onMessage(QString message);
    void onDisconnected();

    void keyPressEvent(QKeyEvent *event);

private:
    QWebSocket *webSocket;
    QSettings *settings;
    QStackedWidget *mainContent;

    ChatWidget *chat;
    DeskWidget *desk;

    QJsonObject m_currentJsonObject;

};

#endif // MAINWINDOW_H
