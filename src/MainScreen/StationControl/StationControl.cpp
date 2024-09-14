#include "StationControl.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QDebug>

StationControl::StationControl(QWidget *parent)
        : QWidget(parent),
          ui(new Ui::StationControll){

    ui->setupUi(this);

    // Set background color of graphicsView to black
    ui->graphicsView->setStyleSheet("background-color: black");

    // Access the existing scene
    QGraphicsScene* scene = ui->graphicsView->scene();
    if (!scene) {
        // If no scene exists, create a new one
        scene = new QGraphicsScene(this);
        ui->graphicsView->setScene(scene);
        qDebug() << "Created a new QGraphicsScene.";
    } else {
        qDebug() << "Using existing QGraphicsScene.";
    }

    // Load the SVG file
    QString svgFilePath = "../layout/layout.svg";
    QFile file(svgFilePath);
    if (!file.exists()) {
        qDebug() << "SVG file does not exist:" << svgFilePath;
        return;
    }

    // Create a ClickableSvgItem and add it to the scene
    ClickableSvgItem* svgItem = new ClickableSvgItem(svgFilePath);
    svgItem->setFlags(QGraphicsItem::ItemClipsToShape);
    svgItem->setCacheMode(QGraphicsItem::NoCache);
    svgItem->setZValue(0);
    svgItem->setScale(10); // Adjust the scale as needed

    // Add the SVG item to the scene
    scene->addItem(svgItem);
    qDebug() << "Added ClickableSvgItem to the scene.";
}

StationControl::~StationControl() {
    delete ui;
    qDebug() << "StationControl destroyed.";
}