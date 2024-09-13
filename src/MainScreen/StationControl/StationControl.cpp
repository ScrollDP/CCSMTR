#include "StationControl.h"
#include "QFrame"

StationControl::StationControl(QWidget *parent) : QWidget(parent) {
    uiSC.setupUi(this);

    //background color of graphics: something between black and darkgray
    uiSC.graphicsView->setBackgroundBrush(QBrush(QColor(50,50,50)));
    //add rails to the ui
    uiSC.graphicsView->setScene(railsScene->railsSceneGraphic);

}

StationControl::~StationControl() {
    delete railsScene;
}
