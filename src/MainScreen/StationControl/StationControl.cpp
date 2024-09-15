#include "StationControl.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QDomDocument>
#include <QDebug>
#include <QFileInfo>

StationControl::StationControl(QWidget *parent)
        : QWidget(parent),
          ui(new Ui::StationControl) {

    ui->setupUi(this);

    // Set background color of graphicsView to black
    ui->graphicsView->setStyleSheet("background-color: black");

    LoadingSvgFile();

}

StationControl::~StationControl() {
    delete ui;
}

void StationControl::LoadingSvgFile() {
    const QString layoutFilePath = QFileInfo("../layout/layout.xml").absoluteFilePath();

    // Create a new scene for the graphicsView
    auto *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    qDebug() << "New QGraphicsScene created.";

    // Ensure the layout file exists
    QFileInfo layoutFileInfo(layoutFilePath);
    if (!layoutFileInfo.exists()) {
        qWarning() << "Layout file does not exist:" << layoutFilePath;
        return;
    }

    // Load the layout XML
    QDomDocument doc;
    QFile file(layoutFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open layout file:" << layoutFilePath << "Error:" << file.errorString();
        return;
    }
    if (!doc.setContent(&file)) {
        qWarning() << "Failed to parse layout file:" << layoutFilePath;
        file.close();
        return;
    }
    file.close();

    // Read layout elements
    QDomElement root = doc.documentElement();
    QDomNodeList elements = root.elementsByTagName("element");

    qDebug() << "Number of elements found:" << elements.count();

    for (int i = 0; i < elements.count(); ++i) {
        QDomElement element = elements.at(i).toElement();
        QString type = element.attribute("type");
        QString id = element.attribute("id");
        int row = element.attribute("row").toInt();
        int col = element.attribute("col").toInt();

        qDebug() << "Element type:" << type << "ID:" << id << "Row:" << row << "Col:" << col;

        QString svgFilePath;
        if (type == "turnout") {
            svgFilePath = QFileInfo("../layout/turnouts/turnout.svg").absoluteFilePath();
        } else if (type == "rail") {
            svgFilePath = QFileInfo("../layout/rails/rail.svg").absoluteFilePath();
        } else {
            continue;
        }

        QFileInfo svgFileInfo(svgFilePath);
        if (!svgFileInfo.exists()) {
            qWarning() << "SVG file does not exist at:" << svgFilePath;
            continue;
        }

        auto *svgItem = new SVGHandleEvent(svgFilePath, id);
        svgItem->setScaleAndPosition(Scale, col * Position_Col, row * Position_Row);

        scene->addItem(svgItem);

        qDebug() << "SVG item added at (" << col * Position_Col << "," << row * Position_Row << ")";
    }
}