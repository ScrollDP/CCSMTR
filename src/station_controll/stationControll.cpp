#include "stationControll.h"
#include "QFrame"

stationControll::stationControll(QWidget *parent) : QWidget(parent) {
    uiSC.setupUi(this);

    //add backgroound color to graphicsView dark grey
    uiSC.graphicsView->setStyleSheet("background-color: #2f2f2f");

    //adding the rails window to the stationControll window
    uiSC.graphicsView->setScene(railsScene->railsSceneGraphic);

}

stationControll::~stationControll() {
    delete railsScene;
}