/********************************************************************************
** Form generated from reading UI file 'ui_MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
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
    QPushButton *actionPower;
    QPushButton *actionDCC_EX;
    QWidget *tools;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QPushButton *actionThrottle;
    QWidget *LayoutEdit;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QCheckBox *checkBox;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1199, 689);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
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
        centralWidget->setObjectName("centralWidget");
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(-1, -1, -1, 0);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
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
        connection->setObjectName("connection");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(connection->sizePolicy().hasHeightForWidth());
        connection->setSizePolicy(sizePolicy2);
        connection->setMaximumSize(QSize(16777215, 100));
        gridLayoutWidget = new QWidget(connection);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(0, 0, 371, 45));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setHorizontalSpacing(15);
        gridLayout->setContentsMargins(5, 5, 5, 5);
        actionPower = new QPushButton(gridLayoutWidget);
        actionPower->setObjectName("actionPower");
        actionPower->setMinimumSize(QSize(110, 35));
        actionPower->setMaximumSize(QSize(110, 35));

        gridLayout->addWidget(actionPower, 0, 1, 1, 1);

        actionDCC_EX = new QPushButton(gridLayoutWidget);
        actionDCC_EX->setObjectName("actionDCC_EX");
        actionDCC_EX->setMinimumSize(QSize(110, 35));
        actionDCC_EX->setMaximumSize(QSize(110, 35));

        gridLayout->addWidget(actionDCC_EX, 0, 0, 1, 1);

        tabWidget->addTab(connection, QString());
        tools = new QWidget();
        tools->setObjectName("tools");
        gridLayoutWidget_2 = new QWidget(tools);
        gridLayoutWidget_2->setObjectName("gridLayoutWidget_2");
        gridLayoutWidget_2->setGeometry(QRect(0, 0, 121, 45));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setHorizontalSpacing(15);
        gridLayout_2->setContentsMargins(5, 5, 5, 5);
        actionThrottle = new QPushButton(gridLayoutWidget_2);
        actionThrottle->setObjectName("actionThrottle");
        actionThrottle->setMinimumSize(QSize(110, 35));
        actionThrottle->setMaximumSize(QSize(110, 35));

        gridLayout_2->addWidget(actionThrottle, 0, 0, 1, 1);

        tabWidget->addTab(tools, QString());
        LayoutEdit = new QWidget();
        LayoutEdit->setObjectName("LayoutEdit");
        gridLayoutWidget_3 = new QWidget(LayoutEdit);
        gridLayoutWidget_3->setObjectName("gridLayoutWidget_3");
        gridLayoutWidget_3->setGeometry(QRect(0, 0, 781, 46));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        checkBox = new QCheckBox(gridLayoutWidget_3);
        checkBox->setObjectName("checkBox");

        gridLayout_3->addWidget(checkBox, 0, 0, 1, 1);

        tabWidget->addTab(LayoutEdit, QString());

        verticalLayout_2->addWidget(tabWidget);


        verticalLayout_4->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        frame = new QFrame(centralWidget);
        frame->setObjectName("frame");
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
        actionPower->setText(QCoreApplication::translate("MainWindow", "Power", nullptr));
        actionDCC_EX->setText(QCoreApplication::translate("MainWindow", "DCC-EX", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(connection), QCoreApplication::translate("MainWindow", "Connection", nullptr));
        actionThrottle->setText(QCoreApplication::translate("MainWindow", "Throttle", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tools), QCoreApplication::translate("MainWindow", "Tools", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "EditMode", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(LayoutEdit), QCoreApplication::translate("MainWindow", "Layout Edit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
