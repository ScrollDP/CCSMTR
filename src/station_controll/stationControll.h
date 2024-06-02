//
// Created by darwin on 26.5.2024.
//

#ifndef CCSMTR_STATIONCONTROLL_H
#define CCSMTR_STATIONCONTROLL_H

#include "ui_stationControll.h"
#include "TurnoutsRails/rails.h"



class stationControll : public QWidget {

public:
    explicit stationControll(QWidget *parent = nullptr);
    ~stationControll() override;


private:
    Ui::stationControll uiSC{};
    rails *railsScene = new rails();

};


#endif //CCSMTR_STATIONCONTROLL_H
