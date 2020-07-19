#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include <QWebSocket>
#include "chat.h"

/**
 * @brief #include
 *
 * Добавил <QJsonObject>
 *
 * @author Nikita Tambov (tambovnikita@yandex.ru)
 */

#include <QJsonObject>
#include <QSettings>


namespace Ui {
class SecondWindow;
}

class SecondWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();
    
    void addMessage(QString message, QString time, QString author);

signals:
    void Mainwindow();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();

    void onConnected();
    void onMessage(QString message);

    void on_pushButton_5_clicked();

    void keyPressEvent(QKeyEvent *event);

private:
    Ui::SecondWindow *ui;
    QWebSocket *webSocket;
    QSettings *settings;

    /**
     * @brief void
     *
     * Добавил json-объект.
     *
     * @author Nikita Tambov (tambovnikita@yandex.ru)
     */
    QJsonObject m_currentJsonObject;

};

#endif // SECONDWINDOW_H
