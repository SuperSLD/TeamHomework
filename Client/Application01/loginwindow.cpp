#include "loginwindow.h"
#include "property.h"

#include <QMessageBox>

#include <QPixmap>
#include <QPalette>
#include <QSettings>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QUrl>
#include <QVBoxLayout>
#include <QPushButton>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent) {
    //Проверка на то был ли пользователь авторизован.
    QSettings *settings = new QSettings("settings.ini", QSettings::IniFormat);
    /*if (settings->value("email", "").toString().length() > 4) {
        openMainWindow();
        return;
    }*/

    QWidget *ui = new QWidget;
    this->setCentralWidget(ui);

    QVBoxLayout *mainVLayout = new QVBoxLayout;
    QVBoxLayout *mainHLayout = new QVBoxLayout;
    QWidget *centerConainer = new QWidget;
    QVBoxLayout *centerLayout = new QVBoxLayout;

    QLabel *titleLabel = new QLabel("<span style='color:#5FB0A9;'>Team</span>"
                                    "<span style='color:white;'>Work</span>");
    QLabel *loginLabel = new QLabel("Почта");
    QLabel *passwordLabel = new QLabel("Пароль");

    QPushButton *loginButton = new QPushButton("Вход");

    QString labelStyle = "color: rgb(255, 255, 255);"
                         "margin-left:20px;"
                         "margin-right:20px;";

    QString centrerContainerStyle = "background-color:#282830;";

    QString buttonStyle = "color: white;"
                          "margin-bottom:20px;"
                          "border:none;";

    QString editTextStyle = "border: 1px solid #5FB0A9;"
                            "color: white;"
                            "height:30px;"
                            "width:300px;"
                            "margin:20px;"
                            "padding:10px;";

    titleLabel->setStyleSheet(labelStyle + "margin-top:20px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    loginLabel->setStyleSheet(labelStyle);
    passwordLabel->setStyleSheet(labelStyle);

    loginButton->setStyleSheet(buttonStyle);
    connect(loginButton, SIGNAL(pressed()), this, SLOT(onLoginButtonActive()));

    loginEdit = new QLineEdit();
    loginEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    loginEdit->setStyleSheet(editTextStyle);
    passwordEdit = new QLineEdit();
    passwordEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setStyleSheet(editTextStyle);

    centerLayout->addWidget(titleLabel);
    centerLayout->addWidget(loginLabel);
    centerLayout->addWidget(loginEdit);
    centerLayout->addWidget(passwordLabel);
    centerLayout->addWidget(passwordEdit);
    centerLayout->addWidget(loginButton);
    centerLayout->setContentsMargins(0,0,0,0);
    centerConainer->setLayout(centerLayout);
    centerConainer->setStyleSheet(centrerContainerStyle);

    mainHLayout->addWidget(centerConainer);
    mainHLayout->setAlignment(Qt::AlignCenter);
    mainVLayout->addLayout(mainHLayout);
    mainVLayout->setAlignment(Qt::AlignCenter);

    ui->setLayout(mainVLayout);
    this->setWindowTitle("Login");
    this->show();
}

LoginWindow::~LoginWindow() {
}

/**
 * @brief MainWindow::resizeEvent
 * @param event
 *
 * Установка фонового изображения на окно авторизации.
 *
 * @author Zinyukov Pavel (FlyForest962@yandex.ru)
 */

void LoginWindow::resizeEvent(QResizeEvent *event)
{
    QPixmap bkgnd(":/resc/resc/back_login.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    QMainWindow::resizeEvent(event);
}

/**
 * @brief MainWindow::on_pushButton_clicked
 *
 * Выполняется при нажатии кнопки Вход.
 *
 * @author Zinyukov Pavel (FlyForest962@yandex.ru)
 */

void LoginWindow::onLoginButtonActive()
{
    QString email = loginEdit->text();
    QString password = passwordEdit->text();

    networkManager = new QNetworkAccessManager();
    // Подключаем networkManager к обработчику ответа
    connect(networkManager, &QNetworkAccessManager::finished, this, &LoginWindow::onResult);
    // Получаем данные, а именно JSON файл с сайта по определённому url
    networkManager->get(
                QNetworkRequest(QUrl(
            "http://jutter.online/TeamServer/auth?email="+email+"&password="+password
                                    )
                )
    );
}

/**
 * @brief MainWindow::onResult
 * @param reply ответ сервера.
 *
 * Обработка ответа с данными пользователя и их проверка.
 *
 * @author Nikita Tambov (tambovnikita@yandex.ru)
 * @author Solyanoy Leonid (solyanoy.leonid@gmail.com)
 */
void LoginWindow::onResult(QNetworkReply *reply)
{
    // Если ошибки отсутсвуют
    if(!reply->error()){
        QString email = loginEdit->text();
        QString password = passwordEdit->text();

        // То создаём объект Json Document, считав в него все данные из ответа
        QByteArray resp = reply->readAll();
        qDebug() << resp << endl;
        QJsonDocument doc = QJsonDocument::fromJson(resp);
        QJsonObject obj;
        if(!doc.isNull()) {
            if(doc.isObject()) {
                obj = doc.object();
                qDebug() << obj["email"].toString() << endl;
            }
            else {
                qDebug() << "Document is not an object" << endl;
            }
        } else {
            qDebug() << "Invalid JSON...\n" << endl;
        }
        if (obj["errcode"].toString() == "0") {
            //сохранение данных.
            QSettings *settings = new QSettings("settings.ini", QSettings::IniFormat);
            settings->setValue("name", obj["name"].toString());
            settings->setValue("lastname", obj["lastname"].toString());
            settings->setValue("password", obj["password"].toString());
            settings->setValue("email", obj["email"].toString());
            settings->setValue("id", obj["id"].toString());
            settings->sync(); //записываем настройки

            //переход к следующему окну.
            openMainWindow();
        } else if (obj["errcode"].toString() == "1"){
            QMessageBox::warning(this, "Ошибка", "Почта не найдена!");
        } else if (obj["errcode"].toString() == "2"){
            QMessageBox::warning(this, "Ошибка", "Неверный пароль!");
        } else if (obj["errcode"].toString() == "3"){
            QMessageBox::warning(this, "Ошибка", "Произошла неизвестная ошибка на сервере!");
        }
    }
    reply->deleteLater();
}

/**
 * @brief MainWindow::openMainWindow
 *
 * Переход к главному окну приложения.
 *
 * @author Solyanoy Leonid (solyanoy.leonid@gmail.com)
 */
void LoginWindow::openMainWindow() {
    hide();
    //mainWindow = new MainWindow();
    //connect(mainWindow, &MainWindow::LoginWindow,this, &LoginWindow::show);
    //mainWindow->show();
    this->close();
}
