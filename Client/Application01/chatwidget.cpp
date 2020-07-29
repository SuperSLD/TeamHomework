#include "chatwidget.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QSizePolicy>
#include <QTextEdit>
#include <QVBoxLayout>

/**
 * @brief ChatWidget::ChatWidget
 *
 * Создание интерфейса для чата.
 *
 * @param webSocket соединение с сервером.
 * @author Solyanoy Leonid (solyanoy.leonid@gmail.com
 */
ChatWidget::ChatWidget(QWebSocket *webSocket)
    : QWidget() {
    this->webSocket = webSocket;
    connect(webSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(onMessage(QString)));

    settings = new QSettings("settings.ini", QSettings::IniFormat);

    maxMessageW = this->width()*0.8;

    QString style = "";
    QFile file(":/resc/qss/chatStyle.css");
    if(file.open(QFile::ReadOnly)) {
          style = QLatin1String(file.readAll());
    } else {
        qDebug() << "style error" << endl;
    }

    QVBoxLayout *mainLayout = new QVBoxLayout;

    scrollMessage = new QScrollArea;
    scrollMessage->setFrameShape(QFrame::NoFrame);
    QWidget *scrolContainer = new QWidget;
    scrolContainer->setObjectName("scrollArea");
    messageLayout = new QVBoxLayout;
    scrolContainer->setLayout(messageLayout);
    scrollMessage->setWidget(scrolContainer);
    scrollMessage->setWidgetResizable(true);
    scrollMessage->horizontalScrollBar()->setEnabled(false);
    QScrollBar *scrollbar = scrollMessage->verticalScrollBar();
    connect(scrollbar, SIGNAL(rangeChanged(int,int)), this, SLOT(moveScrollBarToBottom(int, int)));

    QHBoxLayout *messageEditor = new QHBoxLayout;
    QFrame *messageEditorContainer = new QFrame;

    messageLineEdit = new QLineEdit;
    messageLineEdit->setObjectName("messageLineEdit");
    QPushButton *sendButton = new QPushButton();
    sendButton->setIcon(QIcon(":/resc/resc/send-white-18dp.svg"));
    sendButton->setObjectName("sendButton");
    connect(sendButton, SIGNAL(clicked()), this, SLOT(sendButtonClicked()));

    messageEditor->addWidget(messageLineEdit);
    messageEditor->addWidget(sendButton);
    messageEditorContainer->setLayout(messageEditor);
    messageEditorContainer->setObjectName("messageEditorContainer");
    messageEditorContainer->setSizePolicy(QSizePolicy::Minimum,
                                          QSizePolicy::Minimum);

    mainLayout->addWidget(scrollMessage);
    mainLayout->addWidget(messageEditorContainer);
    mainLayout->setAlignment(Qt::AlignBottom);
    mainLayout->setContentsMargins(0,0,0,0);

    this->setStyleSheet(style);
    this->setLayout(mainLayout);
}

/**
 * @brief ChatWidget::~ChatWidget
 *
 * Просто деструктор. Ничего необычного.
 */
ChatWidget::~ChatWidget() {
    delete webSocket;
    delete messageLayout;
    delete messageLineEdit;

    delete settings;
    delete scrollMessage;
}

/**
 * @brief ChatWidget::onMessage
 *
 * Получение сообщения с сервера.
 *
 * @param message приходящее json сообщение.
 * @author Solyanoy Leonid (solyanoy.leonid@gmail.com)
 */
void ChatWidget::onMessage(QString message){
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject obj;
    if(!doc.isNull()) {
        if(doc.isObject()) {
            obj = doc.object();
        }
        else {
            qDebug() << "Document is not an object" << endl;
        }
    } else {
        qDebug() << "Invalid JSON...\n" << message << endl;
    }

    QString messasgeType = obj["type"].toString();

    if (messasgeType == "group_message") {
        //обработка сообщения группового чата.
        bool isThisUser = (settings->value("name", "default").toString()
                           + " " + settings->value("lastname", "default").toString())
                == obj["author"].toString();
        this->addMessage(
                obj["author"].toString(),
                obj["message"].toString(),
                obj["time"].toString(),
                isThisUser
        );
    }
}

/**
 * @brief ChatWidget::addMessage
 *
 *  Добавление сообщения в разметку.
 *
 * @param author автор сообщения.
 * @param text текст сообщения.
 * @param time время отправки сообщения.
 * @param isThhisUser проверка на отправителя для выбора стиля.
 * @author Solyanoy Leonid (solyanoy.leonid@gmail.com)
 */
void ChatWidget::addMessage(QString author,
                            QString text,
                            QString time,
                            bool isThhisUser) {
    QHBoxLayout *messageLayout = new QHBoxLayout;
    QFrame *messageContainer = new QFrame;
    QVBoxLayout *messageContainerLayout = new QVBoxLayout;

    QLabel *timeLabel = new QLabel(time);

    if (isThhisUser) {
        messageContainer->setObjectName("thisUser");
        messageLayout->setAlignment(Qt::AlignRight);
        timeLabel->setObjectName("timeThisUser");
    } else {
        messageContainer->setObjectName("otherUser");
        QLabel *authorLabel = new QLabel(author);
        authorLabel->setObjectName("author");
        messageContainerLayout->addWidget(authorLabel);
        messageLayout->setAlignment(Qt::AlignLeft);
        timeLabel->setObjectName("time");
    }

    QLabel *textLabel = new QLabel;
    textLabel->setObjectName("text");
    timeLabel->setAlignment(Qt::AlignRight);
    textLabel->setSizePolicy(QSizePolicy::Maximum,
                             QSizePolicy::Maximum);
    messageContainerLayout->addWidget(textLabel);
    messageContainerLayout->addWidget(timeLabel);

    messageContainer->setLayout(messageContainerLayout);
    messageContainer->setMaximumWidth(this->maxMessageW);
    messageLayout->addWidget(messageContainer);


    textLabel->setText(text);
    this->splitMessage(textLabel);

    this->messageLayout->addLayout(messageLayout);
}

/**
 * @brief ChatWidget::sendButtonClicked
 *
 * Слот нажатия на кнопку отпраки сообщения.
 *
 * @author Solyanoy Leonid (solyanoy.leonid@gmail.com)
 */
void ChatWidget::sendButtonClicked() {
   this->sendMessage();
}

/**
 * @brief ChatWidget::sendMessage
 *
 * Отправка сообщения на сервер.
 *
 * @author Solyanoy Leonid (solyanoy.leonid@gmail.com)
 */
void ChatWidget::sendMessage() {
    QString message = messageLineEdit->text();

    if (message==""){

    } else {
        // Создаём объект текста
        QJsonObject textObject;
        textObject["message"] = messageLineEdit->text();  // Устанавливаем message
        textObject["author"] = (settings->value("name", "default").toString()
                                + " " + settings->value("lastname", "default").toString());  // Устанавливаем author
        textObject["type"] = "group_message";  // Устанавливаем type
        textObject["message_type"] = "simple_message";  // Устанавливаем message_type

        QJsonDocument doc(textObject);
        QString strJson(doc.toJson(QJsonDocument::Compact));
        messageLineEdit->setText("");
        webSocket->sendTextMessage(strJson);
    }
}

/**
 * @brief ChatWidget::moveScrollBarToBottom
 *
 * Прокрутка скролбара вниз при добавлении сообщения.
 *
 * @param min
 * @param max
 *
 * @author Solyanoy Leonid (solyanoy.leonid@gmail.com)
 */
void ChatWidget::moveScrollBarToBottom(int min, int max) {
    Q_UNUSED(min);
    scrollMessage->verticalScrollBar()->setValue(max);
}

/**
 * @brief ChatWidget::splitMessage
 *
 * Добавление переносов к сообщению.
 *
 * @param text лейбл в который необходимо добавить
 * переходы на новую строку.
 *
 * @author Solyanoy Leonid (solyanoy.leonid@gmail.com)
 */
void ChatWidget::splitMessage(QLabel *text) {
    QFontMetrics fm(text->font());
    QString message = text->text();
    int pixelsW = fm.width(message)*1.2;

    qDebug() << pixelsW << " / " << this->maxMessageW*0.8 << endl;
    int lineCount = (int) (pixelsW / (this->maxMessageW*0.8)) + 1;
    qDebug() << lineCount << endl;
    int symbolInLine = message.length()/lineCount;
    for (int i = 1; i < lineCount; i++) {
        if (message[i * symbolInLine] == " ") {
            message.insert(i * symbolInLine, "\n");
        } else {
            message.insert(i * symbolInLine, "-\n");
        }
    }
    text->setText(message);
}
