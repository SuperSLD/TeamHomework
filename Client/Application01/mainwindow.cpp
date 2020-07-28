#include "MainWindow.h"
#include "property.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QTime>
#include <QtGui>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QSettings>

#include <QScrollArea>
#include <QScrollBar>
#include <QGridLayout>
#include <QtCore>
#include <QDesktopWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QApplication>


/**
 * @brief SecondWindow::SecondWindow
 * @param parent
 *
 * Создание окна главного меню. Выпонляется при успешной авторизации.
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {

    QString style = "";
    QFile file(":/resc/qss/mainWindowStyle.css");
    if(file.open(QFile::ReadOnly)) {
          style = QLatin1String(file.readAll());
    } else {
        qDebug() << "style error" << endl;
    }

    QWidget *ui = new QWidget;
    ui->setObjectName("ui");
    QHBoxLayout *mainLayout = new QHBoxLayout;
    QFrame *menuContainer = new QFrame;
    mainContent = new QStackedWidget;

    ChatWidget *chat = new ChatWidget(webSocket);

    mainContent->addWidget(chat);
    mainContent->setObjectName("mainContent");
    mainContent->setCurrentIndex(0);

    //Боковое меню
    QVBoxLayout *menuTopLayout = new QVBoxLayout;
     QVBoxLayout *menuBottomLayout = new QVBoxLayout;
    QVBoxLayout *menuMainLayout = new QVBoxLayout;
    QFrame *headitem = new QFrame;
    QVBoxLayout *headContaiter = new QVBoxLayout;
    QLabel *userIcon = new QLabel;
    QPixmap pix1(":/resc/resc/1.jpg");

    QLabel *nameLabel = new QLabel;
    QLabel *lastnameLabel = new QLabel;
    QLabel *emailLabel = new QLabel;

    QPushButton *chatButton = new QPushButton("Сообщения");
    QPushButton *filesButton = new QPushButton("Файлы");
    QPushButton *deskButton = new QPushButton("Задачи");
    QPushButton *exitButon = new QPushButton("Выйти");

    settings = new QSettings("settings.ini", QSettings::IniFormat);

    nameLabel->setText(settings->value("name", "default").toString());
    nameLabel->setObjectName("name");
    lastnameLabel->setText(settings->value("lastname", "default").toString());
    lastnameLabel->setObjectName("lastname");
    emailLabel->setText(settings->value("email", "default").toString());
    emailLabel->setObjectName("email");

    chatButton->setObjectName("menuButton");
    chatButton->setIcon(
        QPixmap(":/resc/resc/chat_bubble_outline-white-18dp.svg"));
    connect(chatButton, SIGNAL(clicked()), this, SLOT(chatButtonClicked()));
    deskButton->setObjectName("menuButton");
    deskButton->setIcon(
                QPixmap(":/resc/resc/chrome_reader_mode-white-18dp.svg"));
    connect(deskButton, SIGNAL(clicked()), this, SLOT(deskButtonClicked()));
    filesButton->setObjectName("menuButton");
    filesButton->setIcon(
                QIcon(":/resc/resc/folder_shared-white-18dp.svg"));
    connect(filesButton, SIGNAL(clicked()), this, SLOT(filesButtonClicked()));
    exitButon->setObjectName("exitButton");
    connect(exitButon, SIGNAL(clicked()), this, SLOT(exitButtonClicked()));

    userIcon->setPixmap(pix1.scaled(50, 50,
                                    Qt::KeepAspectRatio));
    headContaiter->addWidget(userIcon);
    headitem->setObjectName("headFrame");
    headitem->setLayout(headContaiter);
    menuTopLayout->addWidget(headitem);
    menuTopLayout->addWidget(nameLabel);
    menuTopLayout->addWidget(lastnameLabel);
    menuTopLayout->addWidget(emailLabel);
    menuTopLayout->addWidget(chatButton);
    menuTopLayout->addWidget(deskButton);
    menuTopLayout->addWidget(filesButton);
    menuTopLayout->setContentsMargins(0,0,0,0);
    menuTopLayout->setSpacing(0);
    menuBottomLayout->addWidget(exitButon);
    menuBottomLayout->setContentsMargins(0,0,0,0);

    menuTopLayout->setAlignment(Qt::AlignTop);
    menuBottomLayout->setAlignment(Qt::AlignBottom);
    menuMainLayout->addLayout(menuTopLayout);
    menuMainLayout->addLayout(menuBottomLayout);
    menuMainLayout->setContentsMargins(0,0,0,0);
    menuContainer->setLayout(menuMainLayout);
    menuContainer->setObjectName("menuContainer");
    menuContainer->setContentsMargins(0,0,0,0);

    mainLayout->addWidget(menuContainer);
    mainLayout->addWidget(mainContent);
    mainLayout->setAlignment(Qt::AlignLeft);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    ui->setLayout(mainLayout);
    this->setStyleSheet(style);
    this->setCentralWidget(ui);
    this->resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
    this->setWindowIcon(QIcon(":/resc/resc/icon.png"));
    this->setWindowTitle("Сообщения");
}

MainWindow::~MainWindow(){
    delete webSocket;
    delete settings;
    delete mainContent;
}

/**
 * @brief SecondWindow::exitButtonClicked
 *
 * Выполняется при нажатии кнопки Выход.
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */

void MainWindow::exitButtonClicked() {
    settings->setValue("name", "");
    settings->setValue("lastname", "");
    settings->setValue("password", "");
    settings->setValue("email", "");
    settings->setValue("id", "");
    settings->sync();

    QApplication::quit();
}

/**
 * @brief SecondWindow::on_pushButton_clicked
 *
 * Выполняется при нажатии кнопки Файлы.
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */

void MainWindow::filesButtonClicked() {
    mainContent->setCurrentIndex(1);
    this->setWindowTitle("Файлы");
}

/**
 * @brief SecondWindow::on_pushButton_4_clicked
 *
 * Выполняется при нажатии кнопки Сообщения.
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */

void MainWindow::chatButtonClicked(){
    mainContent->setCurrentIndex(0);
    this->setWindowTitle("Сообщения");
}

/**
 * @brief SecondWindow::on_pushButton_3_clicked
 *
 * Выполняется при нажатии кнопки Задачи.
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */

void MainWindow::deskButtonClicked(){
    /*ui->label_7->setText("Здесь скоро появятся Задачи");
    ui->stackedWidget->setCurrentIndex(3);*/
    this->setWindowTitle("Задачи");
}

/**
 * @brief SecondWindow::onConnected
 *
 * Выполняется при успешном подключении вебсокета.
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */
void MainWindow::onConnected() {
    /*ui->stackedWidget->setCurrentIndex(2);
    ui->label_4->setText("WebSocket подключен");
    ui->onlineLabel->setText("<html><head><head/><body><p><span class=\"name\" style=\"color:#9EFFB1;"
                            " font-family:consolas;\">online</span></p></body></html>");

    QJsonObject textObject;
    textObject["id"] = settings->value("id").toString();
    textObject["key"] = settings->value("password").toString();
    textObject["type"] = "connect_user";

    QJsonDocument doc(textObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    webSocket->sendTextMessage(strJson);*/
}

/**
 * @brief SecondWindow::onDisconnected
 *
 * Вызвывается при закрытии вебсокета.
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */
void MainWindow::onDisconnected() {
    /*ui->onlineLabel->setText("<html><head><head/><body><p><span class=\"name\" style=\"color:#FF5964;"
                            " font-family:consolas;\">ofline</span></p></body></html>");
    ui->label_4->setText("WebSocket не подключен");*/
}

/**
 * @brief SecondWindow::onMessage
 * @param string входяшее сообщение
 *
 * Обработка входящих сообщений.
 * Каждое сообщение имеет type в зависимости от
 * которого их необходимо обрабатывать разным способом.
 *
 * отправка обратных сообщений:
 * webSocket->sendTextMessage("Hello From Qt!!!");
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 * @author Kuklin Egor(kuklin_99@bk.ru)
 */
void MainWindow::onMessage(QString string) {
    /*
    //создаем JSON object из строки.
    QJsonDocument doc = QJsonDocument::fromJson(string.toUtf8());
    QJsonObject obj;
    if(!doc.isNull()) {
        if(doc.isObject()) {
            obj = doc.object();
        }
        else {
            qDebug() << "Document is not an object" << endl;
        }
    } else {
        qDebug() << "Invalid JSON...\n" << string << endl;
    }

    QString messasgeType = obj["type"].toString();

    if (messasgeType == "ping") {
        //обработка тестового пинг сообщения.
    } else if (messasgeType == "group_message") {
        //обработка сообщения группового чата.
        addMessage(obj["message"].toString(),
                   obj["time"].toString(),
                   obj["author"].toString());
    }
    */
}

/**
 * @brief SecondWindow::on_pushButton_5_clicked
 *
 * Отправка сообщений в чат с указанием отправителя и время отправки.
 *
 * @author Zinyukov Pavel (FlyForest962@yandex.ru) (Пустая функция.)
 * @author Nikita Tambov (tambovnikita@yandex.ru) (Преобразование сообщений в JSON.)
 */

void MainWindow::on_pushButton_5_clicked() {
    /*
    QString message = ui->lineEdit->text();

    if (message==""){

    } else {
        // Создаём объект текста
        QJsonObject textObject;
        textObject["message"] = ui->lineEdit->text();  // Устанавливаем message
        textObject["author"] = (settings->value("name", "default").toString()
                                + " " + settings->value("lastname", "default").toString());  // Устанавливаем author
        textObject["type"] = "group_message";  // Устанавливаем type
        textObject["message_type"] = "simple_message";  // Устанавливаем message_type

        QJsonDocument doc(textObject);
        QString strJson(doc.toJson(QJsonDocument::Compact));
        webSocket->sendTextMessage(strJson);
    }
    */
}


/**
 * @brief SecondWindow::addMessage
 * @param message текст сообщения.
 * @param time время отправки (а не время получения).
 * @param author автор сообщения.
 * 
 * Вставка сообщения в чат.
 * 
 * @author Zinyukov Pavel (FlyForest962@yandex.ru) (написал весь код)
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 * (обернул в функцию и немного доработал внешний вид сообщений)
 *
 * @author Nikita Tambov (tambovnikita@yandex.ru)
 * (Автоматическая прокрутка чата.)
 */
 void MainWindow::addMessage(QString message, QString time, QString author) {
    /*QLabel *authorLabel = new QLabel ();
    QLabel *timeLabel = new QLabel ();
    QLabel *messageContent = new QLabel();
    QString authorColor = "white";
    if (author == (settings->value("name", "default").toString()
                   + " " + settings->value("lastname", "default").toString())) {
        authorColor = "#87FFD5";
    }

    //Создание сообщения.
    QVBoxLayout *messageBox = new QVBoxLayout();
    QHBoxLayout *messageTitle = new QHBoxLayout();

    authorLabel->setText("<html><head><head/><body><p><span class=\"name\" style=\"color:"+authorColor+";"
                    " font-family:arial;\">"+author+"</span></p></body></html>");
    authorLabel->setStyleSheet("QLabel {"
                               "border-style: solid;"
                               "border-width: 1px;"
                               "border-color: #808080; "
                               "border-radius: 10px;"
                               "}");
    timeLabel->setText("<html><head><head/><body><p><span style=\" "
                    "color:#808080; font-family:arial;\"> "+time+"</span></p></body></html>");
    messageContent->setText(message);
    messageTitle->addWidget(authorLabel);
    messageTitle->addWidget(timeLabel);
    messageBox->addLayout(messageTitle);
    messageBox->addWidget(messageContent);
    messageBox->setAlignment(messageTitle, Qt::AlignLeft);
    messageBox->setAlignment(messageContent, Qt::AlignLeft);

    ui->verticalLayout->addLayout(messageBox);

    ui->lineEdit->clear();
    ui->scrollArea->verticalScrollBar()->setValue(
            ui->scrollArea->verticalScrollBar()->maximumHeight());*/
}

/**
 * @brief SecondWindow::keyPressEvent
 * @param event
 *
 * Отправка сообщения в чат с помощью кнопки Enter.
 *
 * @author Zinyukov Pavel (FlyForest962@yandex.ru)
 * @author Nikita Tambov (tambovnikita@yandex.ru) (Преобразование сообщений в JSON.)
 */

void MainWindow::keyPressEvent(QKeyEvent *event) {
    /*
    //не самый лучший момент
    //дублирование большого куска кода
    //TODO вынести этот кусок в функцию
    if (event->key()==Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        QString str3 = ui->lineEdit->text();
        if (str3=="")
        {

        }
        else
        {
            QJsonObject textObject;
            textObject["message"] = ui->lineEdit->text();  // Устанавливаем message
            textObject["author"] = (settings->value("name", "default").toString()
                                    + " " + settings->value("lastname", "default").toString());  // Устанавливаем author
            textObject["type"] = "group_message";  // Устанавливаем type
            textObject["message_type"] = "simple_message";  // Устанавливаем message_type

            QJsonDocument doc(textObject);
            QString strJson(doc.toJson(QJsonDocument::Compact));
            webSocket->sendTextMessage(strJson);
        }
    }*/
}

/*
    settings = new QSettings("settings.ini", QSettings::IniFormat);
    ui->label_5->setPixmap(pix1.scaled(w, h, Qt::KeepAspectRatio));
    ui->label_3->setText(settings->value("name", "default").toString());
    ui->label->setText(settings->value("lastname", "default").toString());
    ui->label_2->setText(settings->value("email", "default").toString());

    ui->scrollArea->setWidgetResizable(true);

    webSocket  = new QWebSocket();
    webSocket->open(QUrl(("ws://jutter.online/TeamServer/connection")));
    //webSocket->open(QUrl(("ws://localhost:8080/TeamServer/connection")));
    connect(webSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(webSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(onMessage(QString)));
    connect(webSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

    Chat *chat = new Chat();
    ui->stackedWidget->addWidget(chat);

 */
