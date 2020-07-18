#include <string>

#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>

/**
 * @brief The HTTPRequest class
 *
 * Класс для реализации отправки http запросов.
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */
class HTTPRequest
{
private:
    std::string url;
    int timeOut;

public:
    HTTPRequest(std::string url, int timeOut);
    ~HTTPRequest();

    std::string get(std::string sring);
    std::string post(std::string sring);
};

#endif // HTTPREQUEST_H

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    // Обработчик данных полученных от объекта QNetworkAccessManager
    void onResult(QNetworkReply *reply);

private:
    Ui::Widget *ui;
    QNetworkAccessManager *networkManager;
};

#endif // WIDGET_H
