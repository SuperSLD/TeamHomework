#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


/**
 * @brief MainWindow::MainWindow
 * @param parent
 *
 * @author Solyanoy Leonid(solyanoy.leonid@gmail.com)
 */
class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
