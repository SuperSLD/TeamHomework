#include <string>

#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

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