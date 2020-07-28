#ifndef DESKWIDGET_H
#define DESKWIDGET_H

#include <QWebSocket>
#include <QWidget>



class DeskWidget : public QWidget{
    Q_OBJECT
private:
    QWebSocket *webSocket;
protected:
public:
    DeskWidget(QWebSocket *websocket);
    ~DeskWidget();
};

#endif // DESKWIDGET_H
