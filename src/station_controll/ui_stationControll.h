/********************************************************************************
** Form generated from reading UI file 'ui_stationControll.ui'
**
** Created by: Qt User Interface Compiler version 5.15.14
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATIONCONTROLL_H
#define UI_STATIONCONTROLL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_stationControll
{
public:
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *stationControll)
    {
        if (stationControll->objectName().isEmpty())
            stationControll->setObjectName(QString::fromUtf8("stationControll"));
        stationControll->resize(892, 812);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stationControll->sizePolicy().hasHeightForWidth());
        stationControll->setSizePolicy(sizePolicy);
        stationControll->setMinimumSize(QSize(0, 0));
        verticalLayout = new QVBoxLayout(stationControll);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        graphicsView = new QGraphicsView(stationControll);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setMinimumSize(QSize(880, 800));

        verticalLayout->addWidget(graphicsView);


        retranslateUi(stationControll);

        QMetaObject::connectSlotsByName(stationControll);
    } // setupUi

    void retranslateUi(QWidget *stationControll)
    {
        stationControll->setWindowTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class stationControll: public Ui_stationControll {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATIONCONTROLL_H
