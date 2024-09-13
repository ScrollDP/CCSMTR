/********************************************************************************
** Form generated from reading UI file 'ui_StationControl.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATIONCONTROL_H
#define UI_STATIONCONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StationControll
{
public:
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *StationControll)
    {
        if (StationControll->objectName().isEmpty())
            StationControll->setObjectName("StationControll");
        StationControll->resize(892, 812);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(StationControll->sizePolicy().hasHeightForWidth());
        StationControll->setSizePolicy(sizePolicy);
        StationControll->setMinimumSize(QSize(0, 0));
        verticalLayout = new QVBoxLayout(StationControll);
        verticalLayout->setObjectName("verticalLayout");
        graphicsView = new QGraphicsView(StationControll);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setMinimumSize(QSize(880, 800));

        verticalLayout->addWidget(graphicsView);


        retranslateUi(StationControll);

        QMetaObject::connectSlotsByName(StationControll);
    } // setupUi

    void retranslateUi(QWidget *StationControll)
    {
        StationControll->setWindowTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class StationControll: public Ui_StationControll {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATIONCONTROL_H
