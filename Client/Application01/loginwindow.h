#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "MainWindow.h"

#include <QMainWindow>

#include <QLineEdit>
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

    void resizeEvent(QResizeEvent *event);

private slots:
    void onLoginButtonActive();

    // Обработчик данных полученных от объекта QNetworkAccessManager
    void onResult(QNetworkReply *reply);

private:
    QWidget ui;
    //MainWindow *mainWindow;
    QNetworkAccessManager *networkManager;

    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;

    void openMainWindow();
};
#endif // LOGINWWINDOW_H
