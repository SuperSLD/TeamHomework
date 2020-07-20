/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QFrame *frame;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_4;
    QVBoxLayout *verticalLayout;
    QFormLayout *layout_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 607);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resc/resc/1.1.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setLocale(QLocale(QLocale::Rundi, QLocale::Burundi));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 3, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 3, 2, 1, 1);

        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setEnabled(true);
        frame->setStyleSheet(QString::fromUtf8("border-image: url(:/resc/resc/back_login2.jpg);"));
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(0);
        gridLayout->setVerticalSpacing(8);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 2, 1, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 4, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        layout_2 = new QFormLayout();
        layout_2->setObjectName(QString::fromUtf8("layout_2"));
        layout_2->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        layout_2->setFormAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);
        layout_2->setHorizontalSpacing(3);
        layout_2->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(frame);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        QFont font;
        font.setPointSize(10);
        lineEdit->setFont(font);
        lineEdit->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);	"));

        layout_2->setWidget(1, QFormLayout::FieldRole, lineEdit);

        lineEdit_2 = new QLineEdit(frame);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setFont(font);
        lineEdit_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);	"));
        lineEdit_2->setEchoMode(QLineEdit::Password);

        layout_2->setWidget(3, QFormLayout::FieldRole, lineEdit_2);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        layout_2->setWidget(0, QFormLayout::FieldRole, label);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        layout_2->setWidget(2, QFormLayout::FieldRole, label_2);


        verticalLayout->addLayout(layout_2);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setFont(font);
        pushButton->setAcceptDrops(false);
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(86, 86, 86);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setFont(font);
        pushButton_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(86, 86, 86);"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 5, 1, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        font1.setPointSize(24);
        font1.setBold(false);
        font1.setWeight(50);
        label_4->setFont(font1);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 1, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 2, 2, 1, 1);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Times New Roman"));
        font2.setPointSize(16);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        label_3->setFont(font2);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 3, 1, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_6, 0, 1, 1, 1);


        gridLayout_2->addWidget(frame, 1, 1, 2, 2);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "WorkTeam", nullptr));
        label->setText(QApplication::translate("MainWindow", "Email:", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Password:", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "\320\222\321\205\320\276\320\264", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#03dac5; font-family:arial;\">Work</span><span style=\" color:white; font-family:arial;\">Team</span></p></body></html>", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\320\222\321\205\320\276\320\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
