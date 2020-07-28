#include <QLabel>
#include <QWebSocket>

class ChatWidget : public QWidget {
private:
    QWebSocket *webSocket;
protected:
public:
    ChatWidget(QWebSocket *webSocket);
    ~ChatWidget();
};
