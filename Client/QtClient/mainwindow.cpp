#include "contentwidget.h"
#include "loginwidget.h"
#include "mainwidget.h"
#include "mainwindow.h"

#include <QLabel>
#include <QWidget>

/**
 * @brief MainWindow::MainWindow
 * @param parent
 *
 * Конструктор главного окна.
 * Создание содержимого экрана.
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    this->stackedWidget = new QStackedWidget();

    // Создание виджетов.
    this->stackedWidget->addWidget(new LoginWidget(this));
    this->stackedWidget->addWidget(new MainWidget(this));

    // Выбор авторизации в качестве стартового виджета.
    // TODO: В будущем выполнить проверку авторизован пользователь или нет.
    this->stackedWidget->setCurrentIndex(0);

    this->setCentralWidget(stackedWidget);
}

/**
 * @brief MainWindow::showContentWidget
 * @param index индекс необходимого виджета.
 *
 * Выбор отображаемого в окне содержимого.
 *
 */
void MainWindow::showContentWidget(int index) {
    if (this->stackedWidget != nullptr) {
        this->stackedWidget->setCurrentIndex(index);
    }
}

MainWindow::~MainWindow() {
    delete stackedWidget;
}

