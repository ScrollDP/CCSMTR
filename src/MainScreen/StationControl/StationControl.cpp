#include "StationControl.h"
#include <QFrame>


StationControl::StationControl(QWidget *parent)
        : QWidget(parent),
        ui(new Ui::StationControll){

    ui->setupUi(this);

    //background color of graphics: something between black and darkgray
    ui->graphicsView->setBackgroundBrush(QBrush(QColor(50,50,50)));
    //add rails to the ui
    ui->graphicsView->setScene(railsScene->railsSceneGraphic);

}

StationControl::~StationControl() {
    delete railsScene;
}
