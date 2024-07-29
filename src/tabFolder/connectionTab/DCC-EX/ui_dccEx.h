/********************************************************************************
** Form generated from reading UI file 'ui_dccEx.ui'
**
** Created by: Qt User Interface Compiler version 5.15.14
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DCCEX_H
#define UI_DCCEX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dccEx
{
public:
    QVBoxLayout *verticalLayout;
    QComboBox *serialPortComboBox;
    QTextEdit *consoleOutput;
    QLineEdit *consoleInput;
    QPushButton *connectButton;
    QPushButton *disconnectButton;

    void setupUi(QWidget *dccEx)
    {
        if (dccEx->objectName().isEmpty())
            dccEx->setObjectName(QString::fromUtf8("dccEx"));
        dccEx->resize(400, 300);
        verticalLayout = new QVBoxLayout(dccEx);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        serialPortComboBox = new QComboBox(dccEx);
        serialPortComboBox->setObjectName(QString::fromUtf8("serialPortComboBox"));

        verticalLayout->addWidget(serialPortComboBox);

        consoleOutput = new QTextEdit(dccEx);
        consoleOutput->setObjectName(QString::fromUtf8("consoleOutput"));

        verticalLayout->addWidget(consoleOutput);

        consoleInput = new QLineEdit(dccEx);
        consoleInput->setObjectName(QString::fromUtf8("consoleInput"));

        verticalLayout->addWidget(consoleInput);

        connectButton = new QPushButton(dccEx);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));

        verticalLayout->addWidget(connectButton);

        disconnectButton = new QPushButton(dccEx);
        disconnectButton->setObjectName(QString::fromUtf8("disconnectButton"));

        verticalLayout->addWidget(disconnectButton);


        retranslateUi(dccEx);

        QMetaObject::connectSlotsByName(dccEx);
    } // setupUi

    void retranslateUi(QWidget *dccEx)
    {
        dccEx->setWindowTitle(QCoreApplication::translate("dccEx", "DCC-EX", nullptr));
        connectButton->setText(QCoreApplication::translate("dccEx", "Connect", nullptr));
        disconnectButton->setText(QCoreApplication::translate("dccEx", "Disconnect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dccEx: public Ui_dccEx {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DCCEX_H
