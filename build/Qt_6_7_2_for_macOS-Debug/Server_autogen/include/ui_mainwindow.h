/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QLabel *labelPort;
    QSpinBox *spinPort;
    QPushButton *StartServer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(324, 125);
        MainWindow->setStyleSheet(QString::fromUtf8("#StartServer[state = \"0\"]{\n"
"	color: rgb(255, 98, 101)\n"
"}\n"
"#StartServer[state = \"1\"]{\n"
"	color: rgb(61, 255, 66);\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName("horizontalLayout");
        labelPort = new QLabel(groupBox);
        labelPort->setObjectName("labelPort");

        horizontalLayout->addWidget(labelPort);

        spinPort = new QSpinBox(groupBox);
        spinPort->setObjectName("spinPort");
        spinPort->setMinimum(1024);
        spinPort->setMaximum(65000);

        horizontalLayout->addWidget(spinPort);

        StartServer = new QPushButton(groupBox);
        StartServer->setObjectName("StartServer");
        StartServer->setAutoDefault(false);
        StartServer->setFlat(false);

        horizontalLayout->addWidget(StartServer);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 324, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        StartServer->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QString());
        labelPort->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\200\321\202", nullptr));
        StartServer->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        StartServer->setProperty("state", QVariant(QString()));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
