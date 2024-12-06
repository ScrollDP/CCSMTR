/********************************************************************************
** Form generated from reading UI file 'ui_StationControl.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATIONCONTROL_H
#define UI_STATIONCONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StationControl
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *Refresh;
    QPushButton *ResetRoutes;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *StationControl)
    {
        if (StationControl->objectName().isEmpty())
            StationControl->setObjectName("StationControl");
        StationControl->resize(892, 812);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(StationControl->sizePolicy().hasHeightForWidth());
        StationControl->setSizePolicy(sizePolicy);
        StationControl->setMinimumSize(QSize(0, 0));
        verticalLayout = new QVBoxLayout(StationControl);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        Refresh = new QPushButton(StationControl);
        Refresh->setObjectName("Refresh");

        horizontalLayout->addWidget(Refresh);

        ResetRoutes = new QPushButton(StationControl);
        ResetRoutes->setObjectName("ResetRoutes");

        horizontalLayout->addWidget(ResetRoutes);


        verticalLayout->addLayout(horizontalLayout);

        graphicsView = new QGraphicsView(StationControl);
        graphicsView->setObjectName("graphicsView");

        verticalLayout->addWidget(graphicsView);


        retranslateUi(StationControl);

        QMetaObject::connectSlotsByName(StationControl);
    } // setupUi

    void retranslateUi(QWidget *StationControl)
    {
        StationControl->setWindowTitle(QString());
        Refresh->setText(QCoreApplication::translate("StationControl", "Refresh SVGs", nullptr));
        ResetRoutes->setText(QCoreApplication::translate("StationControl", "reset routes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StationControl: public Ui_StationControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATIONCONTROL_H
