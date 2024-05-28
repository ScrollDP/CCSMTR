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
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *connection;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_2;
    QPushButton *actionDCC_EX;
    QPushButton *actionIntelibox_I;
    QWidget *tools;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QPushButton *actionThrottle;
    QPushButton *actionTurnouts;
    QVBoxLayout *verticalLayout_4;
    QFrame *frame;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(805, 478);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(0, 150));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setPointSize(10);
        MainWindow->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, -1, -1, 0);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setMinimumSize(QSize(0, 0));
        tabWidget->setMaximumSize(QSize(16777215, 85));
        tabWidget->setBaseSize(QSize(0, 0));
        QFont font1;
        font1.setPointSize(15);
        tabWidget->setFont(font1);
        tabWidget->setTabPosition(QTabWidget::TabPosition::North);
        tabWidget->setDocumentMode(false);
        connection = new QWidget();
        connection->setObjectName(QString::fromUtf8("connection"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(connection->sizePolicy().hasHeightForWidth());
        connection->setSizePolicy(sizePolicy2);
        connection->setMaximumSize(QSize(16777215, 100));
        formLayoutWidget_2 = new QWidget(connection);
        formLayoutWidget_2->setObjectName(QString::fromUtf8("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(0, 0, 261, 41));
        formLayout_2 = new QFormLayout(formLayoutWidget_2);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setHorizontalSpacing(10);
        formLayout_2->setContentsMargins(5, 5, 0, 0);
        actionDCC_EX = new QPushButton(formLayoutWidget_2);
        actionDCC_EX->setObjectName(QString::fromUtf8("actionDCC_EX"));
        actionDCC_EX->setMaximumSize(QSize(110, 35));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, actionDCC_EX);

        actionIntelibox_I = new QPushButton(formLayoutWidget_2);
        actionIntelibox_I->setObjectName(QString::fromUtf8("actionIntelibox_I"));
        actionIntelibox_I->setMaximumSize(QSize(110, 35));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, actionIntelibox_I);

        tabWidget->addTab(connection, QString());
        tools = new QWidget();
        tools->setObjectName(QString::fromUtf8("tools"));
        formLayoutWidget = new QWidget(tools);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(0, 0, 241, 41));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setHorizontalSpacing(10);
        formLayout->setContentsMargins(5, 5, 0, 0);
        actionThrottle = new QPushButton(formLayoutWidget);
        actionThrottle->setObjectName(QString::fromUtf8("actionThrottle"));
        actionThrottle->setMaximumSize(QSize(110, 35));

        formLayout->setWidget(0, QFormLayout::LabelRole, actionThrottle);

        actionTurnouts = new QPushButton(formLayoutWidget);
        actionTurnouts->setObjectName(QString::fromUtf8("actionTurnouts"));
        actionTurnouts->setMaximumSize(QSize(110, 35));

        formLayout->setWidget(0, QFormLayout::FieldRole, actionTurnouts);

        tabWidget->addTab(tools, QString());

        verticalLayout_2->addWidget(tabWidget);


        verticalLayout->addLayout(verticalLayout_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);

        verticalLayout_4->addWidget(frame);


        verticalLayout->addLayout(verticalLayout_4);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "CCSMTR", nullptr));
        actionDCC_EX->setText(QCoreApplication::translate("MainWindow", "DCC-EX", nullptr));
        actionIntelibox_I->setText(QCoreApplication::translate("MainWindow", "Intelibox I", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(connection), QCoreApplication::translate("MainWindow", "Connection", nullptr));
        actionThrottle->setText(QCoreApplication::translate("MainWindow", "Throttle", nullptr));
        actionTurnouts->setText(QCoreApplication::translate("MainWindow", "Turnouts", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tools), QCoreApplication::translate("MainWindow", "Tools", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
