/********************************************************************************
** Form generated from reading UI file 'ui_DccEx.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
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

class Ui_DccEx
{
public:
    QVBoxLayout *verticalLayout;
    QComboBox *serialPortComboBox;
    QTextEdit *consoleOutput;
    QLineEdit *consoleInput;
    QPushButton *connectButton;
    QPushButton *disconnectButton;

    void setupUi(QWidget *DccEx)
    {
        if (DccEx->objectName().isEmpty())
            DccEx->setObjectName("DccEx");
        DccEx->resize(400, 300);
        verticalLayout = new QVBoxLayout(DccEx);
        verticalLayout->setObjectName("verticalLayout");
        serialPortComboBox = new QComboBox(DccEx);
        serialPortComboBox->setObjectName("serialPortComboBox");

        verticalLayout->addWidget(serialPortComboBox);

        consoleOutput = new QTextEdit(DccEx);
        consoleOutput->setObjectName("consoleOutput");

        verticalLayout->addWidget(consoleOutput);

        consoleInput = new QLineEdit(DccEx);
        consoleInput->setObjectName("consoleInput");

        verticalLayout->addWidget(consoleInput);

        connectButton = new QPushButton(DccEx);
        connectButton->setObjectName("connectButton");

        verticalLayout->addWidget(connectButton);

        disconnectButton = new QPushButton(DccEx);
        disconnectButton->setObjectName("disconnectButton");

        verticalLayout->addWidget(disconnectButton);


        retranslateUi(DccEx);

        QMetaObject::connectSlotsByName(DccEx);
    } // setupUi

    void retranslateUi(QWidget *DccEx)
    {
        DccEx->setWindowTitle(QCoreApplication::translate("DccEx", "DCC-EX", nullptr));
        connectButton->setText(QCoreApplication::translate("DccEx", "Connect", nullptr));
        disconnectButton->setText(QCoreApplication::translate("DccEx", "Disconnect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DccEx: public Ui_DccEx {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DCCEX_H
