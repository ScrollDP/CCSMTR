/********************************************************************************
** Form generated from reading UI file 'ui_ThrottleWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THROTTLEWINDOW_H
#define UI_THROTTLEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ThrottleWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_7;
    QLabel *AdressLabel;
    QLineEdit *inputAdress;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_5;
    QPushButton *AquireButton;
    QPushButton *EmergencyStop;
    QVBoxLayout *verticalLayout_6;
    QPushButton *ReleaseButton;
    QPushButton *EmergencyPause;
    QGridLayout *gridLayout;
    QPushButton *F3;
    QPushButton *F14;
    QPushButton *F5;
    QPushButton *F13;
    QPushButton *F0;
    QPushButton *F8;
    QPushButton *F12;
    QPushButton *F16;
    QPushButton *F4;
    QPushButton *F15;
    QPushButton *F7;
    QPushButton *F6;
    QPushButton *F25;
    QPushButton *F28;
    QPushButton *F27;
    QPushButton *F1;
    QPushButton *F10;
    QPushButton *F2;
    QPushButton *F26;
    QPushButton *F9;
    QPushButton *F11;
    QPushButton *F17;
    QPushButton *F18;
    QPushButton *F19;
    QPushButton *F20;
    QPushButton *F21;
    QPushButton *F22;
    QPushButton *F23;
    QPushButton *F24;
    QVBoxLayout *verticalLayout_3;
    QLabel *speedLabel;
    QSlider *speedSlider;
    QPushButton *ForwardSpeed;
    QPushButton *ReverseSpeed;

    void setupUi(QMainWindow *ThrottleWindow)
    {
        if (ThrottleWindow->objectName().isEmpty())
            ThrottleWindow->setObjectName(QString::fromUtf8("ThrottleWindow"));
        ThrottleWindow->resize(456, 478);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ThrottleWindow->sizePolicy().hasHeightForWidth());
        ThrottleWindow->setSizePolicy(sizePolicy);
        ThrottleWindow->setMinimumSize(QSize(456, 478));
        ThrottleWindow->setMaximumSize(QSize(456, 478));
        centralWidget = new QWidget(ThrottleWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, -1, -1);
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(5, 5, 2, 5);
        AdressLabel = new QLabel(centralWidget);
        AdressLabel->setObjectName(QString::fromUtf8("AdressLabel"));
        AdressLabel->setMaximumSize(QSize(16777215, 50));
        QFont font;
        font.setPointSize(15);
        AdressLabel->setFont(font);
        AdressLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_7->addWidget(AdressLabel);

        inputAdress = new QLineEdit(centralWidget);
        inputAdress->setObjectName(QString::fromUtf8("inputAdress"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(inputAdress->sizePolicy().hasHeightForWidth());
        inputAdress->setSizePolicy(sizePolicy1);
        inputAdress->setMinimumSize(QSize(100, 40));
        inputAdress->setMaximumSize(QSize(16777215, 50));
        inputAdress->setFont(font);

        verticalLayout_7->addWidget(inputAdress);


        verticalLayout_4->addLayout(verticalLayout_7);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(5, 5, 2, 5);
        AquireButton = new QPushButton(centralWidget);
        AquireButton->setObjectName(QString::fromUtf8("AquireButton"));
        QFont font1;
        font1.setPointSize(14);
        AquireButton->setFont(font1);

        verticalLayout_5->addWidget(AquireButton);

        EmergencyStop = new QPushButton(centralWidget);
        EmergencyStop->setObjectName(QString::fromUtf8("EmergencyStop"));
        EmergencyStop->setFont(font);

        verticalLayout_5->addWidget(EmergencyStop);


        horizontalLayout_2->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(2, 5, 2, 5);
        ReleaseButton = new QPushButton(centralWidget);
        ReleaseButton->setObjectName(QString::fromUtf8("ReleaseButton"));
        ReleaseButton->setFont(font1);

        verticalLayout_6->addWidget(ReleaseButton);

        EmergencyPause = new QPushButton(centralWidget);
        EmergencyPause->setObjectName(QString::fromUtf8("EmergencyPause"));
        EmergencyPause->setFont(font);

        verticalLayout_6->addWidget(EmergencyPause);


        horizontalLayout_2->addLayout(verticalLayout_6);


        verticalLayout_4->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout_4);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(5, -1, 2, 5);
        F3 = new QPushButton(centralWidget);
        F3->setObjectName(QString::fromUtf8("F3"));
        F3->setMinimumSize(QSize(50, 50));
        F3->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F3, 0, 3, 1, 1);

        F14 = new QPushButton(centralWidget);
        F14->setObjectName(QString::fromUtf8("F14"));
        F14->setMinimumSize(QSize(50, 50));
        F14->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F14, 2, 2, 1, 1);

        F5 = new QPushButton(centralWidget);
        F5->setObjectName(QString::fromUtf8("F5"));
        F5->setMinimumSize(QSize(50, 50));
        F5->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F5, 0, 5, 1, 1);

        F13 = new QPushButton(centralWidget);
        F13->setObjectName(QString::fromUtf8("F13"));
        F13->setMinimumSize(QSize(50, 50));
        F13->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F13, 2, 1, 1, 1);

        F0 = new QPushButton(centralWidget);
        F0->setObjectName(QString::fromUtf8("F0"));
        F0->setMinimumSize(QSize(50, 50));
        F0->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F0, 0, 0, 1, 1);

        F8 = new QPushButton(centralWidget);
        F8->setObjectName(QString::fromUtf8("F8"));
        F8->setMinimumSize(QSize(50, 50));
        F8->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F8, 1, 2, 1, 1);

        F12 = new QPushButton(centralWidget);
        F12->setObjectName(QString::fromUtf8("F12"));
        F12->setMinimumSize(QSize(50, 50));
        F12->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F12, 2, 0, 1, 1);

        F16 = new QPushButton(centralWidget);
        F16->setObjectName(QString::fromUtf8("F16"));
        F16->setMinimumSize(QSize(50, 50));
        F16->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F16, 2, 4, 1, 1);

        F4 = new QPushButton(centralWidget);
        F4->setObjectName(QString::fromUtf8("F4"));
        F4->setMinimumSize(QSize(50, 50));
        F4->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F4, 0, 4, 1, 1);

        F15 = new QPushButton(centralWidget);
        F15->setObjectName(QString::fromUtf8("F15"));
        F15->setMinimumSize(QSize(50, 50));
        F15->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F15, 2, 3, 1, 1);

        F7 = new QPushButton(centralWidget);
        F7->setObjectName(QString::fromUtf8("F7"));
        F7->setMinimumSize(QSize(50, 50));
        F7->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F7, 1, 1, 1, 1);

        F6 = new QPushButton(centralWidget);
        F6->setObjectName(QString::fromUtf8("F6"));
        F6->setMinimumSize(QSize(50, 50));
        F6->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F6, 1, 0, 1, 1);

        F25 = new QPushButton(centralWidget);
        F25->setObjectName(QString::fromUtf8("F25"));
        F25->setMinimumSize(QSize(50, 50));
        F25->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F25, 4, 1, 1, 1);

        F28 = new QPushButton(centralWidget);
        F28->setObjectName(QString::fromUtf8("F28"));
        F28->setMinimumSize(QSize(50, 50));
        F28->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F28, 4, 4, 1, 1);

        F27 = new QPushButton(centralWidget);
        F27->setObjectName(QString::fromUtf8("F27"));
        F27->setMinimumSize(QSize(50, 50));
        F27->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F27, 4, 3, 1, 1);

        F1 = new QPushButton(centralWidget);
        F1->setObjectName(QString::fromUtf8("F1"));
        F1->setMinimumSize(QSize(50, 50));
        F1->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F1, 0, 1, 1, 1);

        F10 = new QPushButton(centralWidget);
        F10->setObjectName(QString::fromUtf8("F10"));
        F10->setMinimumSize(QSize(50, 50));
        F10->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F10, 1, 4, 1, 1);

        F2 = new QPushButton(centralWidget);
        F2->setObjectName(QString::fromUtf8("F2"));
        F2->setMinimumSize(QSize(50, 50));
        F2->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F2, 0, 2, 1, 1);

        F26 = new QPushButton(centralWidget);
        F26->setObjectName(QString::fromUtf8("F26"));
        F26->setMinimumSize(QSize(50, 50));
        F26->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F26, 4, 2, 1, 1);

        F9 = new QPushButton(centralWidget);
        F9->setObjectName(QString::fromUtf8("F9"));
        F9->setMinimumSize(QSize(50, 50));
        F9->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F9, 1, 3, 1, 1);

        F11 = new QPushButton(centralWidget);
        F11->setObjectName(QString::fromUtf8("F11"));
        F11->setMinimumSize(QSize(50, 50));
        F11->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F11, 1, 5, 1, 1);

        F17 = new QPushButton(centralWidget);
        F17->setObjectName(QString::fromUtf8("F17"));
        F17->setMinimumSize(QSize(50, 50));
        F17->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F17, 2, 5, 1, 1);

        F18 = new QPushButton(centralWidget);
        F18->setObjectName(QString::fromUtf8("F18"));
        F18->setMinimumSize(QSize(50, 50));
        F18->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F18, 3, 0, 1, 1);

        F19 = new QPushButton(centralWidget);
        F19->setObjectName(QString::fromUtf8("F19"));
        F19->setMinimumSize(QSize(50, 50));
        F19->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F19, 3, 1, 1, 1);

        F20 = new QPushButton(centralWidget);
        F20->setObjectName(QString::fromUtf8("F20"));
        F20->setMinimumSize(QSize(50, 50));
        F20->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F20, 3, 2, 1, 1);

        F21 = new QPushButton(centralWidget);
        F21->setObjectName(QString::fromUtf8("F21"));
        F21->setMinimumSize(QSize(50, 50));
        F21->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F21, 3, 3, 1, 1);

        F22 = new QPushButton(centralWidget);
        F22->setObjectName(QString::fromUtf8("F22"));
        F22->setMinimumSize(QSize(50, 50));
        F22->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F22, 3, 4, 1, 1);

        F23 = new QPushButton(centralWidget);
        F23->setObjectName(QString::fromUtf8("F23"));
        F23->setMinimumSize(QSize(50, 50));
        F23->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F23, 3, 5, 1, 1);

        F24 = new QPushButton(centralWidget);
        F24->setObjectName(QString::fromUtf8("F24"));
        F24->setMinimumSize(QSize(50, 50));
        F24->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(F24, 4, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        verticalLayout_3->setContentsMargins(2, 5, 5, 5);
        speedLabel = new QLabel(centralWidget);
        speedLabel->setObjectName(QString::fromUtf8("speedLabel"));
        speedLabel->setFont(font);
        speedLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(speedLabel);

        speedSlider = new QSlider(centralWidget);
        speedSlider->setObjectName(QString::fromUtf8("speedSlider"));
        speedSlider->setMinimumSize(QSize(100, 0));
        speedSlider->setMaximumSize(QSize(100, 16777215));
        speedSlider->setOrientation(Qt::Orientation::Vertical);

        verticalLayout_3->addWidget(speedSlider);

        ForwardSpeed = new QPushButton(centralWidget);
        ForwardSpeed->setObjectName(QString::fromUtf8("ForwardSpeed"));
        ForwardSpeed->setFont(font);

        verticalLayout_3->addWidget(ForwardSpeed);

        ReverseSpeed = new QPushButton(centralWidget);
        ReverseSpeed->setObjectName(QString::fromUtf8("ReverseSpeed"));
        ReverseSpeed->setFont(font);

        verticalLayout_3->addWidget(ReverseSpeed);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout->addLayout(horizontalLayout);

        ThrottleWindow->setCentralWidget(centralWidget);

        retranslateUi(ThrottleWindow);

        QMetaObject::connectSlotsByName(ThrottleWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ThrottleWindow)
    {
        ThrottleWindow->setWindowTitle(QCoreApplication::translate("ThrottleWindow", "Throttle", nullptr));
        AdressLabel->setText(QCoreApplication::translate("ThrottleWindow", "Adress", nullptr));
        AquireButton->setText(QCoreApplication::translate("ThrottleWindow", "Aquire", nullptr));
        EmergencyStop->setText(QCoreApplication::translate("ThrottleWindow", "STOP", nullptr));
        ReleaseButton->setText(QCoreApplication::translate("ThrottleWindow", "Release", nullptr));
        EmergencyPause->setText(QCoreApplication::translate("ThrottleWindow", "PAUSE", nullptr));
        F3->setText(QCoreApplication::translate("ThrottleWindow", "F3", nullptr));
        F14->setText(QCoreApplication::translate("ThrottleWindow", "F14", nullptr));
        F5->setText(QCoreApplication::translate("ThrottleWindow", "F5", nullptr));
        F13->setText(QCoreApplication::translate("ThrottleWindow", "F13", nullptr));
        F0->setText(QCoreApplication::translate("ThrottleWindow", "F0", nullptr));
        F8->setText(QCoreApplication::translate("ThrottleWindow", "F8", nullptr));
        F12->setText(QCoreApplication::translate("ThrottleWindow", "F12", nullptr));
        F16->setText(QCoreApplication::translate("ThrottleWindow", "F16", nullptr));
        F4->setText(QCoreApplication::translate("ThrottleWindow", "F4", nullptr));
        F15->setText(QCoreApplication::translate("ThrottleWindow", "F15", nullptr));
        F7->setText(QCoreApplication::translate("ThrottleWindow", "F7", nullptr));
        F6->setText(QCoreApplication::translate("ThrottleWindow", "F6", nullptr));
        F25->setText(QCoreApplication::translate("ThrottleWindow", "F25", nullptr));
        F28->setText(QCoreApplication::translate("ThrottleWindow", "F28", nullptr));
        F27->setText(QCoreApplication::translate("ThrottleWindow", "F27", nullptr));
        F1->setText(QCoreApplication::translate("ThrottleWindow", "F1", nullptr));
        F10->setText(QCoreApplication::translate("ThrottleWindow", "F10", nullptr));
        F2->setText(QCoreApplication::translate("ThrottleWindow", "F2", nullptr));
        F26->setText(QCoreApplication::translate("ThrottleWindow", "F26", nullptr));
        F9->setText(QCoreApplication::translate("ThrottleWindow", "F9", nullptr));
        F11->setText(QCoreApplication::translate("ThrottleWindow", "F11", nullptr));
        F17->setText(QCoreApplication::translate("ThrottleWindow", "F17", nullptr));
        F18->setText(QCoreApplication::translate("ThrottleWindow", "F18", nullptr));
        F19->setText(QCoreApplication::translate("ThrottleWindow", "F19", nullptr));
        F20->setText(QCoreApplication::translate("ThrottleWindow", "F20", nullptr));
        F21->setText(QCoreApplication::translate("ThrottleWindow", "F21", nullptr));
        F22->setText(QCoreApplication::translate("ThrottleWindow", "F22", nullptr));
        F23->setText(QCoreApplication::translate("ThrottleWindow", "F23", nullptr));
        F24->setText(QCoreApplication::translate("ThrottleWindow", "F24", nullptr));
        speedLabel->setText(QCoreApplication::translate("ThrottleWindow", "Speed", nullptr));
        ForwardSpeed->setText(QCoreApplication::translate("ThrottleWindow", "Forward", nullptr));
        ReverseSpeed->setText(QCoreApplication::translate("ThrottleWindow", "Reverse", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ThrottleWindow: public Ui_ThrottleWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THROTTLEWINDOW_H
