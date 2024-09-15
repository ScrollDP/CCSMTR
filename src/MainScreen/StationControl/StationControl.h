#ifndef CCSMTR_STATIONCONTROL_H
#define CCSMTR_STATIONCONTROL_H

#include "ui_stationControl.h"
#include <QWidget>
#include <QDomDocument>
#include <QGraphicsSvgItem>


class StationControl : public QWidget {
    Q_OBJECT

public:
    explicit StationControl(QWidget *parent = nullptr);
    ~StationControl() override;  // Ensure the destructor is declared here

private:
    Ui::StationControl *ui;
    static void setScaleAndPosition(QGraphicsSvgItem *item, qreal scale, qreal x, qreal y);

    int Scale = 30;
    int Position_Col = 8;
    int Position_Row = 12;
};


#endif //CCSMTR_STATIONCONTROL_H
