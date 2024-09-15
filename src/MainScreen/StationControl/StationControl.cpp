#include "StationControl.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QDomDocument>
#include <QDebug>
#include <QFileInfo>
#include <unordered_map>

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
    const QString layoutFilePath = QFileInfo("../layout/layout.xml").filePath();

    // Create a new scene for the graphicsView
    auto *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    qDebug() << "New QGraphicsScene created.";

    QFile file(layoutFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open layout file:" << layoutFilePath;
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qWarning() << "Failed to parse layout file:" << layoutFilePath;
        file.close();
        return;
    }
    file.close();

    // Create a map to handle the file paths
    std::unordered_map<QString, QString> typeToFilePath = {
            {"turnout", QFileInfo("../layout/turnouts/turnout.svg").filePath()},
            {"rail", QFileInfo("../layout/rails/rail.svg").filePath()}
    };

    QDomElement root = doc.documentElement();
    QDomNodeList categories = root.childNodes();
    for (int i = 0; i < categories.count(); ++i) {
        QDomNode categoryNode = categories.at(i);
        QDomNodeList elements = categoryNode.childNodes();
        for (int j = 0; j < elements.count(); ++j) {
            QDomElement element = elements.at(j).toElement();
            QString type = element.attribute("type");
            QString id = element.attribute("id");
            int row = element.attribute("row").toInt();
            int col = element.attribute("col").toInt();

            qDebug() << "Element type:" << type << "ID:" << id << "Row:" << row << "Col:" << col;

            // Use the map to get the file path
            auto it = typeToFilePath.find(type);
            if (it == typeToFilePath.end()) {
                qWarning() << "Invalid type:" << type;
                continue;
            }
            QString svgFilePath = it->second;

            QFileInfo svgFileInfo(svgFilePath);
            if (!svgFileInfo.exists()) {
                qWarning() << "SVG file does not exist at:" << svgFilePath;
                continue;
            }

            // Load the SVG file
            auto *svgItem = new SVGHandleEvent(svgFilePath, id);
            svgItem->setScaleAndPosition(Scale, col * Position_Col, row * Position_Row);

            scene->addItem(svgItem);

            qDebug() << "SVG item added at (" << col * Position_Col << "," << row * Position_Row << ")";
        }
    }
}