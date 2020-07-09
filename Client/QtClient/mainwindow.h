#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>


/**
 * @brief MainWindow::MainWindow
 * @param parent
 *
 * Класс главного окна приложения.
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */
class MainWindow : public QMainWindow{
    Q_OBJECT
private:
    QStackedWidget *stackedWidget;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showContentWidget(int index);
};
#endif // MAINWINDOW_H
