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

private:
    Ui::SecondWindow *ui;
    QWebSocket *webSocket;

    /**
     * @brief void
     *
     * Добавил слоты и json-объект.
     *
     * @author Nikita Tambov (tambovnikita@yandex.ru)
     */

    // Слот добавления нового текста в массив текстов
    void onAddButtonClicked();
    // Слот удаления всей информации о текстах в текущем объекте
    void onClearButtonClicked();
    // Слот сохранения текстов в json файл
    void onSaveButtonClicked();
    // Слот загрузки текстов в программу из json файла
    void onLoadButtonClicked();


    // Текущий json объект, с которым производится работа
    QJsonObject m_currentJsonObject;
    
};

#endif // SECONDWINDOW_H
