#include <QLabel>
#include <QLineEdit>
#include <QScrollArea>
#include <QSettings>
#include <QVBoxLayout>
#include <QWebSocket>

/**
 * @brief The ChatWidget class
 *
 * Виджет для отделения логики
 * чата от главного окна.
 *
 * @author Solyanoy Leonid (solyanoy.leonid@gmail.com)
 */
class ChatWidget : public QWidget {
    Q_OBJECT
private:

    QWebSocket *webSocket;
    QVBoxLayout *messageLayout;
    QLineEdit *messageLineEdit;
    QSettings *settings;
    QScrollArea *scrollMessage;
    int maxMessageW;

    void addMessage(QString author,QString text,QString time,bool isThhisUser);
    void splitMessage(QLabel *text);

private slots:

    void onMessage(QString message);
    void moveScrollBarToBottom(int min, int max);

    void sendButtonClicked();
    void clearLayout(QLayout *layout);

protected:

public:

    ChatWidget(QWebSocket *webSocket);
    ~ChatWidget();
    void sendMessage();
    void clearChat();

};
