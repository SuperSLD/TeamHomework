#include "httprequest.h"

#define _WIN32_WINNT 0x0A00
#define BOOST_DATE_TIME_NO_LIB
#define BOOST_REGEX_NO_LIB

#include <iostream>

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

std::string get(std::string sring) {

    return nullptr;
}
