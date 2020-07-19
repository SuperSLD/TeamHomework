#ifndef CHAT_H
#define CHAT_H

#include <QLabel>

namespace Ui {
class Chat;
}

class Chat : public QLabel
{
    Q_OBJECT

public:
    explicit Chat(QWidget *parent = nullptr);
    ~Chat();

private:
    Ui::Chat *ui;

};

#endif // CHAT_H
