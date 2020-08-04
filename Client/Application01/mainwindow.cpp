#include "mainwindow.h"
#include "deskwidget.h"
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

    webSocket  = new QWebSocket();

    connect(webSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(webSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(onMessage(QString)));
    connect(webSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(webSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));

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

    chat = new ChatWidget(webSocket);
    desk = new DeskWidget(webSocket);

    mainContent->addWidget(chat);
    mainContent->addWidget(desk);
    mainContent->setObjectName("mainContent");
    mainContent->setCurrentIndex(0);

    //Боковое меню
    QVBoxLayout *menuTopLayout = new QVBoxLayout;
    QVBoxLayout *menuBottomLayout = new QVBoxLayout;
    QVBoxLayout *menuMainLayout = new QVBoxLayout;
    QFrame *headitem = new QFrame;
    QVBoxLayout *headContaiter = new QVBoxLayout;
    QLabel *userIcon = new QLabel;
    QPixmap pix1(":/resc/resc/user.png");

    QLabel *nameLabel = new QLabel;
    QLabel *lastnameLabel = new QLabel;
    QLabel *emailLabel = new QLabel;
    onlineLabel = new QLabel("ofline");

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
    onlineLabel->setObjectName("onlineLabel");

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
    headContaiter->addWidget(nameLabel);
    headContaiter->addWidget(lastnameLabel);
    headContaiter->addWidget(emailLabel);
    headContaiter->addWidget(onlineLabel);
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

    webSocket->open(QUrl(("ws://jutter.online/TeamServer/connection")));
    //webSocket->open(QUrl(("ws://localhost:8080/TeamServer/connection")));
}

MainWindow::~MainWindow(){
    delete webSocket;
    delete settings;
    delete mainContent;

    delete chat;
    delete desk;
    delete onlineLabel;
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
    mainContent->setCurrentIndex(2);
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
    mainContent->setCurrentIndex(1);
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
    onlineLabel->setText("online");

    QJsonObject textObject;
    textObject["id"] = settings->value("id").toString();
    textObject["key"] = settings->value("password").toString();
    textObject["type"] = "connect_user";

    QJsonDocument doc(textObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    webSocket->sendTextMessage(strJson);
}

/**
 * @brief SecondWindow::onDisconnected
 *
 * Вызвывается при закрытии вебсокета.
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */
void MainWindow::onDisconnected() {
    onlineLabel->setText("ofline");
    webSocket->abort();
    //webSocket->open(QUrl(("ws://jutter.online/TeamServer/connection")));
}

/**
 * @brief MainWindow::onError
 *
 * Обработка ошибок вебсокета и попытка переподключиться.
 *
 * @param error
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */
void MainWindow::onError(QAbstractSocket::SocketError error) {
    Q_UNUSED(error)
    //webSocket->open(QUrl(("ws://jutter.online/TeamServer/connection")));
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
    }
}

/**
 * @brief SecondWindow::keyPressEvent
 * @param event
 *
 * Отправка сообщения в чат с помощью кнопки Enter.
 *
 * @author Zinyukov Pavel (FlyForest962@yandex.ru)
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if ((event->key()==Qt::Key_Enter || event->key() == Qt::Key_Return)
            && mainContent->currentIndex() == 0) {
        chat->sendMessage();
    }
}
