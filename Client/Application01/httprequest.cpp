#include "httprequest.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>

/**
 * @brief HTTPRequest::HTTPRequest
 * @param url адрес.
 * @param timeOut ограничение по времени.
 *
 * Конструктор для объекта запросов.
 */
HTTPRequest::HTTPRequest(std::string url, int timeOut) {
    this->url = url;
    this->timeOut = timeOut;
}

/**
 * @brief get
 * @param sring окончание адреса запроса.
 * @return строка полученная с сервера.
 */
std::string get(std::string sring) {
    //TODO: написать реализацию метода.

    /*
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkReply *response = manager->get(QNetworkRequest(QUrl("https://yandex.ru/")));
    */

    return nullptr;
}
