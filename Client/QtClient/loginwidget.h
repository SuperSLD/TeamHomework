#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include "contentwidget.h"


/**
 * @brief The LoginWidget class
 *
 * Авторизация польщователя.
 */
class LoginWidget : public ContentWidget {
public:
    LoginWidget(MainWindow *window, QWidget *parent = nullptr);
    ~LoginWidget();
};

#endif // LOGINWIDGET_H
