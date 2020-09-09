#include "deskwidget.h"

#include <QFile>
#include <QLabel>
#include <QVBoxLayout>
#include <QWebSocket>

/**
 * @brief DeskWidget::DeskWidget
 *
 * Создание разметки дрски задач.
 *
 * @param webSocket соединение с сервером.
 * @author Solyanoy Leonid (solyanoy.leonid@gmail.com
 */
DeskWidget::DeskWidget(QWebSocket *webSocket)
    : QWidget() {
    this->webSocket = webSocket;

    QHBoxLayout *ui = new QHBoxLayout;

    QString style = "";
    QFile file(":/resc/qss/deskStyle.css");
    if(file.open(QFile::ReadOnly)) {
          style = QLatin1String(file.readAll());
    } else {
        qDebug() << "style error" << endl;
    }

    QVBoxLayout *taskColumn = new QVBoxLayout;
    QVBoxLayout *progressColumn = new QVBoxLayout;
    QVBoxLayout *resultColumn = new QVBoxLayout;

    QLabel *taskLabel = new QLabel("Задачи");
    QLabel *progressLabel = new QLabel("В процессе");
    QLabel *resultLabel = new QLabel("Выполненные задачи");
    taskLabel->setObjectName("titleColumn");
    taskLabel->setAlignment(Qt::AlignCenter);
    progressLabel->setObjectName("titleColumn");
    progressLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setObjectName("titleColumn");
    resultLabel->setAlignment(Qt::AlignCenter);

    taskColumn->addWidget(taskLabel);
    progressColumn->addWidget(progressLabel);
    resultColumn->addWidget(resultLabel);


    ui->addLayout(taskColumn);
    ui->addLayout(progressColumn);
    ui->addLayout(resultColumn);
    ui->setAlignment(Qt::AlignTop);
    this->setLayout(ui);
    this->setStyleSheet(style);
}

DeskWidget::~DeskWidget() {
    delete webSocket;
}
