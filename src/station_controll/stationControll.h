//
// Created by darwin on 26.5.2024.
//

#ifndef CCSMTR_STATIONCONTROLL_H
#define CCSMTR_STATIONCONTROLL_H

#include "ui_stationControll.h"
#include "Rails/Rails.h"



class stationControll : public QWidget {

public:
    explicit stationControll(QWidget *parent = nullptr);
    ~stationControll() override;

private:
    Ui::stationControll uiSC{};
    Rails *railsScene = new Rails();

};


#endif //CCSMTR_STATIONCONTROLL_H
