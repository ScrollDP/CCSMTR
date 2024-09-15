#ifndef CCSMTR_STATIONCONTROL_H
#define CCSMTR_STATIONCONTROL_H

#include "ui_stationControl.h"
#include <QWidget>
#include <QDomDocument>
#include <QGraphicsSvgItem>
#include "../../LogicInstance/StationControlLogic/SVGHandleEvent/SVGHandleEvent.h"

class StationControl : public QWidget {
    Q_OBJECT

public:
    explicit StationControl(QWidget *parent = nullptr);
    ~StationControl() override;  // Ensure the destructor is declared here

private:
    Ui::StationControl *ui;
    void LoadingSvgFile();

    int Scale = 20;
    int Position_Col = 8;
    int Position_Row = 12;

    static void ApplyTransformation(bool mirror, int rotate, SVGHandleEvent* svgHandleEvent);
};


#endif //CCSMTR_STATIONCONTROL_H
