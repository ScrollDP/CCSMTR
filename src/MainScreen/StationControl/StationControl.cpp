#include "StationControl.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QGraphicsSvgItem>
#include <QSvgRenderer>

StationControl::StationControl(QWidget *parent)
        : QWidget(parent),
          ui(new Ui::StationControll) {

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

    // Load the layout.svg file
    ClickableSvgItem* svgItem = new ClickableSvgItem();
    QString filePath = QStringLiteral("../layout/layout.svg");
    QSvgRenderer* renderer = new QSvgRenderer(filePath);

    if (!renderer->isValid()) {
        qDebug() << "Failed to load SVG file:" << filePath;
    } else {
        qDebug() << "Successfully loaded SVG file:" << filePath;
    }

    svgItem->setSharedRenderer(renderer);
    scene->addItem(svgItem);
    svgItem->setScale(10);
}

StationControl::~StationControl() {
    delete ui;
}