/********************************************************************************
** Form generated from reading UI file 'ui_PowerWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POWERWINDOW_H
#define UI_POWERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PowerWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QPushButton *PowerOnMain;
    QPushButton *PowerOffMain;
    QPushButton *PowerOffProg;
    QPushButton *PowerOff;
    QPushButton *PowerOnProg;
    QPushButton *PowerOn;
    QPushButton *PowerOnJoin;

    void setupUi(QMainWindow *PowerWindow)
    {
        if (PowerWindow->objectName().isEmpty())
            PowerWindow->setObjectName("PowerWindow");
        PowerWindow->resize(327, 256);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PowerWindow->sizePolicy().hasHeightForWidth());
        PowerWindow->setSizePolicy(sizePolicy);
        PowerWindow->setMinimumSize(QSize(0, 0));
        PowerWindow->setMaximumSize(QSize(327, 256));
        centralWidget = new QWidget(PowerWindow);
        centralWidget->setObjectName("centralWidget");
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMaximumSize(QSize(327, 256));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(5, 5, 5, 5);
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setMaximumSize(QSize(16777215, 50));
        QFont font;
        font.setPointSize(15);
        label->setFont(font);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label);


        verticalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        gridLayout->setHorizontalSpacing(15);
        gridLayout->setVerticalSpacing(10);
        gridLayout->setContentsMargins(5, 5, 5, 5);
        PowerOnMain = new QPushButton(centralWidget);
        PowerOnMain->setObjectName("PowerOnMain");
        PowerOnMain->setMaximumSize(QSize(150, 50));
        PowerOnMain->setFont(font);

        gridLayout->addWidget(PowerOnMain, 1, 0, 1, 1);

        PowerOffMain = new QPushButton(centralWidget);
        PowerOffMain->setObjectName("PowerOffMain");
        PowerOffMain->setMaximumSize(QSize(150, 50));
        PowerOffMain->setFont(font);

        gridLayout->addWidget(PowerOffMain, 1, 1, 1, 1);

        PowerOffProg = new QPushButton(centralWidget);
        PowerOffProg->setObjectName("PowerOffProg");
        PowerOffProg->setMaximumSize(QSize(150, 50));
        PowerOffProg->setFont(font);

        gridLayout->addWidget(PowerOffProg, 2, 1, 1, 1);

        PowerOff = new QPushButton(centralWidget);
        PowerOff->setObjectName("PowerOff");
        PowerOff->setMaximumSize(QSize(150, 50));
        PowerOff->setFont(font);

        gridLayout->addWidget(PowerOff, 0, 1, 1, 1);

        PowerOnProg = new QPushButton(centralWidget);
        PowerOnProg->setObjectName("PowerOnProg");
        PowerOnProg->setMaximumSize(QSize(150, 50));
        PowerOnProg->setFont(font);

        gridLayout->addWidget(PowerOnProg, 2, 0, 1, 1);

        PowerOn = new QPushButton(centralWidget);
        PowerOn->setObjectName("PowerOn");
        PowerOn->setMaximumSize(QSize(150, 50));
        PowerOn->setFont(font);

        gridLayout->addWidget(PowerOn, 0, 0, 1, 1);

        PowerOnJoin = new QPushButton(centralWidget);
        PowerOnJoin->setObjectName("PowerOnJoin");
        PowerOnJoin->setMaximumSize(QSize(150, 50));
        PowerOnJoin->setFont(font);

        gridLayout->addWidget(PowerOnJoin, 3, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout);


        verticalLayout->addLayout(verticalLayout_2);

        PowerWindow->setCentralWidget(centralWidget);

        retranslateUi(PowerWindow);

        QMetaObject::connectSlotsByName(PowerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PowerWindow)
    {
        PowerWindow->setWindowTitle(QCoreApplication::translate("PowerWindow", "Power", nullptr));
        label->setText(QCoreApplication::translate("PowerWindow", "Nap\303\241janie trate", nullptr));
        PowerOnMain->setText(QCoreApplication::translate("PowerWindow", "PowerOnMain", nullptr));
        PowerOffMain->setText(QCoreApplication::translate("PowerWindow", "PowerOffMain", nullptr));
        PowerOffProg->setText(QCoreApplication::translate("PowerWindow", "PowerOffProg", nullptr));
        PowerOff->setText(QCoreApplication::translate("PowerWindow", "PowerOff", nullptr));
        PowerOnProg->setText(QCoreApplication::translate("PowerWindow", "PowerOnProg", nullptr));
        PowerOn->setText(QCoreApplication::translate("PowerWindow", "PowerOn", nullptr));
        PowerOnJoin->setText(QCoreApplication::translate("PowerWindow", "PowerOnJoin", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PowerWindow: public Ui_PowerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POWERWINDOW_H
