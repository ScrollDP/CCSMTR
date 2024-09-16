#include "StationControl.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QDomDocument>
#include <QDebug>
#include <QFileInfo>
#include <unordered_map>
#include <QTransform>
#include <QRegularExpression>

StationControl::StationControl(QWidget *parent, const QString &svgFilePath)
        : QWidget(parent),
          renderer(new QSvgRenderer(svgFilePath)),
          ui(new Ui::StationControl) {

    ui->setupUi(this);

    // Set background color of graphicsView to black
    ui->graphicsView->setStyleSheet("background-color: black");

    LoadingSvgFile();

    connect(ui->Refresh, &QPushButton::clicked, this, [svgFilePath, this]() {
        LoadingSvgFile();
    });

}

StationControl::~StationControl() {
    delete ui;
}

void StationControl::LoadingSvgFile() {
    const QString layoutFilePath = QFileInfo("../layout/layout.xml").filePath();

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

    std::unordered_map<QString, QString> typeToFilePath = {
            {"turnout",       QFileInfo("../layout/turnouts/turnout.svg").filePath()},
            {"turnout_sklon",QFileInfo("../layout/turnouts/turnout_sklon.svg").filePath()},
            {"rail",          QFileInfo("../layout/rails/rail.svg").filePath()},
            {"cross_turnout", QFileInfo("../layout/turnouts/cross_turnout.svg").filePath()},
            {"rail_sklon1",    QFileInfo("../layout/rails/rail_sklon1.svg").filePath()},
            {"rail_sklon2",    QFileInfo("../layout/rails/rail_sklon2.svg").filePath()},
            {"rail_sklon3",    QFileInfo("../layout/rails/rail_sklon3.svg").filePath()},
            {"rail_sklon4",    QFileInfo("../layout/rails/rail_sklon4.svg").filePath()}

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
            bool flipped = element.attribute("flipped").toLower() == "true";
            int rotate = element.attribute("rotate").toInt();


            qDebug() << "Element type:" << type << "ID:" << id << "Row:" << row << "Col:" << col;

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

            // Create a temporary file
            QString tmpFilePath = QString(".tmp/tmp_%1_%2.svg").arg(type).arg(id);
            QFile tmpFile(tmpFilePath);
            if (tmpFile.exists()) {
                tmpFile.remove(); // Delete the temporary file if it exists
            }
            QFile::copy(svgFilePath, tmpFilePath); // Copy the original file to the temporary location


            // Load the temporary SVG file
            auto *svgItem = new SVGHandleEvent(tmpFilePath, id);
            svgItem->setScaleAndPosition(Scale, col * Position_Col, row * Position_Row);

            ApplyTransformation(flipped, rotate, svgItem, type);

            scene->addItem(svgItem);

            qDebug() << "SVG item added at (" << col * Position_Col << "," << row * Position_Row << ")";
        }
    }
}

void StationControl::ApplyTransformation(bool flipped, int rotate, SVGHandleEvent *svgItem, QString type) {
    QString transformStr;

    if(type == "turnout"){
        if (rotate == 0) {
            if (flipped) {
                transformStr = "scale(-1, 1) translate(-8,0) rotate(0)";
            } else {
                transformStr = "scale(1, 1) translate(0,0) rotate(0)";
            }
        } else if (rotate == 90) {
            if (flipped) {
                transformStr = "scale(-1, 1) translate(-1,2) rotate(90)";
            } else {
                transformStr = "scale(-1, -1) translate(-1,-10) rotate(90)";
            }
        } else if (rotate == 180) {
            if (flipped) {
                transformStr = "scale(-1, 1) translate(0,12) rotate(180)";
            } else {
                transformStr = "scale(1, 1) translate(8,12) rotate(180)";
            }
        } else if (rotate == 270) {
            if (flipped) {
                transformStr = "scale(-1, 1) translate(-7,10) rotate(270)";
            } else {
                transformStr = "scale(-1, -1) translate(-7,-2) rotate(270)";
            }
        }
    }
    if(type == "turnout_sklon"){


    }

    svgItem->updateTransform(transformStr);
}