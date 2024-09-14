#ifndef CCSMTR_STATIONCONTROL_H
#define CCSMTR_STATIONCONTROL_H

#include "ui_stationControl.h"
#include "../../LogicInstance/StationControlLogic/ClickableSvgItem/ClickableSvgItem.h"


class StationControl : public QWidget {

public:
    explicit StationControl(QWidget *parent = nullptr);
    ~StationControl() override;

private:
    Ui::StationControll *ui;
    //Rails *railsScene = new Rails();

};


#endif //CCSMTR_STATIONCONTROL_H
