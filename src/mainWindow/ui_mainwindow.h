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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *connection;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *actionIntelibox_I;
    QPushButton *actionDCC_EX;
    QPushButton *actionPower;
    QWidget *tools;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QPushButton *actionThrottle;
    QPushButton *actionTurnouts;
    QWidget *LayoutEdit;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1199, 689);
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
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, -1, -1, 0);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setMinimumSize(QSize(377, 85));
        tabWidget->setMaximumSize(QSize(16777215, 85));
        tabWidget->setBaseSize(QSize(0, 0));
        QFont font1;
        font1.setPointSize(15);
        tabWidget->setFont(font1);
        tabWidget->setMouseTracking(false);
        tabWidget->setTabPosition(QTabWidget::TabPosition::North);
        tabWidget->setTabShape(QTabWidget::TabShape::Rounded);
        tabWidget->setIconSize(QSize(16, 16));
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(false);
        tabWidget->setTabBarAutoHide(false);
        connection = new QWidget();
        connection->setObjectName(QString::fromUtf8("connection"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(connection->sizePolicy().hasHeightForWidth());
        connection->setSizePolicy(sizePolicy2);
        connection->setMaximumSize(QSize(16777215, 100));
        gridLayoutWidget = new QWidget(connection);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 371, 45));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(15);
        gridLayout->setContentsMargins(5, 5, 5, 5);
        actionIntelibox_I = new QPushButton(gridLayoutWidget);
        actionIntelibox_I->setObjectName(QString::fromUtf8("actionIntelibox_I"));
        actionIntelibox_I->setMinimumSize(QSize(110, 35));
        actionIntelibox_I->setMaximumSize(QSize(110, 35));

        gridLayout->addWidget(actionIntelibox_I, 0, 1, 1, 1);

        actionDCC_EX = new QPushButton(gridLayoutWidget);
        actionDCC_EX->setObjectName(QString::fromUtf8("actionDCC_EX"));
        actionDCC_EX->setMinimumSize(QSize(110, 35));
        actionDCC_EX->setMaximumSize(QSize(110, 35));

        gridLayout->addWidget(actionDCC_EX, 0, 0, 1, 1);

        actionPower = new QPushButton(gridLayoutWidget);
        actionPower->setObjectName(QString::fromUtf8("actionPower"));
        actionPower->setMinimumSize(QSize(110, 35));
        actionPower->setMaximumSize(QSize(110, 35));

        gridLayout->addWidget(actionPower, 0, 2, 1, 1);

        tabWidget->addTab(connection, QString());
        tools = new QWidget();
        tools->setObjectName(QString::fromUtf8("tools"));
        gridLayoutWidget_2 = new QWidget(tools);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(0, 0, 241, 45));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(15);
        gridLayout_2->setContentsMargins(5, 5, 5, 5);
        actionThrottle = new QPushButton(gridLayoutWidget_2);
        actionThrottle->setObjectName(QString::fromUtf8("actionThrottle"));
        actionThrottle->setMinimumSize(QSize(110, 35));
        actionThrottle->setMaximumSize(QSize(110, 35));

        gridLayout_2->addWidget(actionThrottle, 0, 0, 1, 1);

        actionTurnouts = new QPushButton(gridLayoutWidget_2);
        actionTurnouts->setObjectName(QString::fromUtf8("actionTurnouts"));
        actionTurnouts->setMinimumSize(QSize(110, 35));
        actionTurnouts->setMaximumSize(QSize(110, 35));

        gridLayout_2->addWidget(actionTurnouts, 0, 1, 1, 1);

        tabWidget->addTab(tools, QString());
        LayoutEdit = new QWidget();
        LayoutEdit->setObjectName(QString::fromUtf8("LayoutEdit"));
        gridLayoutWidget_3 = new QWidget(LayoutEdit);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(0, 0, 781, 46));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        tabWidget->addTab(LayoutEdit, QString());

        verticalLayout_2->addWidget(tabWidget);


        verticalLayout_4->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);

        verticalLayout_3->addWidget(frame);


        verticalLayout_4->addLayout(verticalLayout_3);


        verticalLayout->addLayout(verticalLayout_4);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "CCSMTR", nullptr));
        actionIntelibox_I->setText(QCoreApplication::translate("MainWindow", "Intelibox I", nullptr));
        actionDCC_EX->setText(QCoreApplication::translate("MainWindow", "DCC-EX", nullptr));
        actionPower->setText(QCoreApplication::translate("MainWindow", "Power", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(connection), QCoreApplication::translate("MainWindow", "Connection", nullptr));
        actionThrottle->setText(QCoreApplication::translate("MainWindow", "Throttle", nullptr));
        actionTurnouts->setText(QCoreApplication::translate("MainWindow", "Turnouts", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tools), QCoreApplication::translate("MainWindow", "Tools", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(LayoutEdit), QCoreApplication::translate("MainWindow", "Layout Edit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
