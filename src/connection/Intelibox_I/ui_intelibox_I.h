/********************************************************************************
** Form generated from reading UI file 'ui_intelibox_I.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTELIBOX_I_H
#define UI_INTELIBOX_I_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_intelibox_I
{
public:
    QVBoxLayout *verticalLayout;
    QComboBox *serialPortComboBox;
    QTextEdit *consoleOutput;
    QLineEdit *consoleInput;
    QPushButton *connectButton;
    QPushButton *disconnectButton;

    void setupUi(QWidget *intelibox_I)
    {
        if (intelibox_I->objectName().isEmpty())
            intelibox_I->setObjectName(QString::fromUtf8("intelibox_I"));
        intelibox_I->resize(400, 300);
        verticalLayout = new QVBoxLayout(intelibox_I);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        serialPortComboBox = new QComboBox(intelibox_I);
        serialPortComboBox->setObjectName(QString::fromUtf8("serialPortComboBox"));

        verticalLayout->addWidget(serialPortComboBox);

        consoleOutput = new QTextEdit(intelibox_I);
        consoleOutput->setObjectName(QString::fromUtf8("consoleOutput"));

        verticalLayout->addWidget(consoleOutput);

        consoleInput = new QLineEdit(intelibox_I);
        consoleInput->setObjectName(QString::fromUtf8("consoleInput"));

        verticalLayout->addWidget(consoleInput);

        connectButton = new QPushButton(intelibox_I);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));

        verticalLayout->addWidget(connectButton);

        disconnectButton = new QPushButton(intelibox_I);
        disconnectButton->setObjectName(QString::fromUtf8("disconnectButton"));

        verticalLayout->addWidget(disconnectButton);


        retranslateUi(intelibox_I);

        QMetaObject::connectSlotsByName(intelibox_I);
    } // setupUi

    void retranslateUi(QWidget *intelibox_I)
    {
        intelibox_I->setWindowTitle(QCoreApplication::translate("intelibox_I", "Intelibox_I", nullptr));
        connectButton->setText(QCoreApplication::translate("intelibox_I", "Connect", nullptr));
        disconnectButton->setText(QCoreApplication::translate("intelibox_I", "Disconnect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class intelibox_I: public Ui_intelibox_I {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTELIBOX_I_H
