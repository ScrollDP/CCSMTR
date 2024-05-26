/********************************************************************************
** Form generated from reading UI file 'ui_mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit_and_Terminate;
    QAction *actionDCC_EX;
    QAction *actionIntelibox_I;
    QAction *actionThrottle;
    QAction *actionTurnouts;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuConnection;
    QMenu *menuThrottle;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionExit_and_Terminate = new QAction(MainWindow);
        actionExit_and_Terminate->setObjectName(QString::fromUtf8("actionExit_and_Terminate"));
        actionDCC_EX = new QAction(MainWindow);
        actionDCC_EX->setObjectName(QString::fromUtf8("actionDCC_EX"));
        actionIntelibox_I = new QAction(MainWindow);
        actionIntelibox_I->setObjectName(QString::fromUtf8("actionIntelibox_I"));
        actionThrottle = new QAction(MainWindow);
        actionThrottle->setObjectName(QString::fromUtf8("actionThrottle"));
        actionTurnouts = new QAction(MainWindow);
        actionTurnouts->setObjectName(QString::fromUtf8("actionTurnouts"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 30));
        menuConnection = new QMenu(menubar);
        menuConnection->setObjectName(QString::fromUtf8("menuConnection"));
        menuThrottle = new QMenu(menubar);
        menuThrottle->setObjectName(QString::fromUtf8("menuThrottle"));
        MainWindow->setMenuBar(menubar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menubar->addAction(menuConnection->menuAction());
        menubar->addAction(menuThrottle->menuAction());
        menuConnection->addAction(actionDCC_EX);
        menuConnection->addAction(actionIntelibox_I);
        menuThrottle->addAction(actionThrottle);
        menuThrottle->addAction(actionTurnouts);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "CCSMTR", nullptr));
        actionExit_and_Terminate->setText(QCoreApplication::translate("MainWindow", "Exit and Terminate", nullptr));
        actionDCC_EX->setText(QCoreApplication::translate("MainWindow", "&DCC-EX", nullptr));
        actionIntelibox_I->setText(QCoreApplication::translate("MainWindow", "&Intelibox I", nullptr));
        actionThrottle->setText(QCoreApplication::translate("MainWindow", "&Throttle", nullptr));
        actionTurnouts->setText(QCoreApplication::translate("MainWindow", "T&urnouts", nullptr));
        menuConnection->setTitle(QCoreApplication::translate("MainWindow", "&Connection", nullptr));
        menuThrottle->setTitle(QCoreApplication::translate("MainWindow", "Too&ls", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
