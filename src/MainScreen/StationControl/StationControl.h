//
// Created by darwin on 26.5.2024.
//

#ifndef CCSMTR_STATIONCONTROL_H
#define CCSMTR_STATIONCONTROL_H

#include "ui_stationControl.h"
#include "../../LogicInstance/StationControlLogic/Rails/Rails.h"



class StationControl : public QWidget {

public:
    explicit StationControl(QWidget *parent = nullptr);
    ~StationControl() override;

private:
    Ui::stationControll uiSC{};
    Rails *railsScene = new Rails();

};


#endif //CCSMTR_STATIONCONTROL_H
