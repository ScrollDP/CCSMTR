/********************************************************************************
** Form generated from reading UI file 'ui_RightClick.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RIGHTCLICK_H
#define UI_RIGHTCLICK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RightClick
{
public:
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *TurnoutLabel;
    QTextEdit *TurnoutID;
    QHBoxLayout *horizontalLayout_2;
    QLabel *Adress;
    QTextEdit *AddressSet;
    QHBoxLayout *horizontalLayout_4;
    QLabel *SwitchTLabel;
    QCheckBox *SwitchCheckBox;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *SaveButton;

    void setupUi(QWidget *RightClick)
    {
        if (RightClick->objectName().isEmpty())
            RightClick->setObjectName(QString::fromUtf8("RightClick"));
        RightClick->resize(416, 399);
        RightClick->setMinimumSize(QSize(300, 200));
        verticalLayout = new QVBoxLayout(RightClick);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 5, -1, 5);
        TurnoutLabel = new QLabel(RightClick);
        TurnoutLabel->setObjectName(QString::fromUtf8("TurnoutLabel"));
        TurnoutLabel->setMinimumSize(QSize(125, 50));
        TurnoutLabel->setMaximumSize(QSize(130, 50));
        QFont font;
        font.setPointSize(15);
        TurnoutLabel->setFont(font);
        TurnoutLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(TurnoutLabel);

        TurnoutID = new QTextEdit(RightClick);
        TurnoutID->setObjectName(QString::fromUtf8("TurnoutID"));
        TurnoutID->setMinimumSize(QSize(50, 50));
        TurnoutID->setMaximumSize(QSize(50, 50));
        TurnoutID->setFont(font);
        TurnoutID->setReadOnly(true);

        horizontalLayout->addWidget(TurnoutID);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 5, -1, 5);
        Adress = new QLabel(RightClick);
        Adress->setObjectName(QString::fromUtf8("Adress"));
        Adress->setMinimumSize(QSize(100, 50));
        Adress->setMaximumSize(QSize(110, 50));
        Adress->setFont(font);
        Adress->setFrameShape(QFrame::Shape::NoFrame);
        Adress->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(Adress);

        AddressSet = new QTextEdit(RightClick);
        AddressSet->setObjectName(QString::fromUtf8("AddressSet"));
        AddressSet->setMinimumSize(QSize(85, 50));
        AddressSet->setMaximumSize(QSize(85, 50));
        AddressSet->setFont(font);

        horizontalLayout_2->addWidget(AddressSet);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        SwitchTLabel = new QLabel(RightClick);
        SwitchTLabel->setObjectName(QString::fromUtf8("SwitchTLabel"));
        SwitchTLabel->setMinimumSize(QSize(125, 50));
        SwitchTLabel->setMaximumSize(QSize(130, 50));
        SwitchTLabel->setFont(font);
        SwitchTLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_4->addWidget(SwitchTLabel);

        SwitchCheckBox = new QCheckBox(RightClick);
        SwitchCheckBox->setObjectName(QString::fromUtf8("SwitchCheckBox"));
        SwitchCheckBox->setMaximumSize(QSize(150, 50));
        SwitchCheckBox->setBaseSize(QSize(0, 0));
        SwitchCheckBox->setFont(font);
        SwitchCheckBox->setIconSize(QSize(16, 16));
        SwitchCheckBox->setAutoRepeatDelay(300);
        SwitchCheckBox->setTristate(false);

        horizontalLayout_4->addWidget(SwitchCheckBox);


        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout->addLayout(verticalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 5, -1, 5);
        SaveButton = new QPushButton(RightClick);
        SaveButton->setObjectName(QString::fromUtf8("SaveButton"));
        SaveButton->setMinimumSize(QSize(95, 45));
        SaveButton->setMaximumSize(QSize(100, 50));
        SaveButton->setFont(font);

        horizontalLayout_3->addWidget(SaveButton);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(RightClick);

        QMetaObject::connectSlotsByName(RightClick);
    } // setupUi

    void retranslateUi(QWidget *RightClick)
    {
        RightClick->setWindowTitle(QCoreApplication::translate("RightClick", "option", nullptr));
        TurnoutLabel->setText(QCoreApplication::translate("RightClick", "Turnout ID:", nullptr));
        Adress->setText(QCoreApplication::translate("RightClick", "Address:", nullptr));
        SwitchTLabel->setText(QCoreApplication::translate("RightClick", "Status switch:", nullptr));
        SwitchCheckBox->setText(QCoreApplication::translate("RightClick", "Switched", nullptr));
        SaveButton->setText(QCoreApplication::translate("RightClick", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RightClick: public Ui_RightClick {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RIGHTCLICK_H
