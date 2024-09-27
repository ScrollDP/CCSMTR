#include "StationControl.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QDomDocument>
#include <QFileInfo>
#include <unordered_map>
#include <QTransform>
#include <QRegularExpression>
#include <QXmlStreamReader>
#include <QString>
#include <QDir>

StationControl::StationControl(QWidget *parent, const QString &svgFilePath)
        : QWidget(parent),
          renderer(new QSvgRenderer(svgFilePath)),
          ui(new Ui::StationControl) {

    ui->setupUi(this);
    ui->Refresh->hide();
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

std::unordered_map<QString, QString> loadTypeToFilePath(const QString &filePath) {
    std::unordered_map<QString, QString> typeToFilePath;
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Cannot open file:" << filePath;
        return typeToFilePath;
    }

    QXmlStreamReader xml(&file);
    while (!xml.atEnd() && !xml.hasError()) {
        xml.readNext();
        if (xml.isStartElement() && xml.name() == QString("location")) {
            QString id = xml.attributes().value("id").toString();
            QString path = xml.attributes().value("path").toString();
            typeToFilePath[id] = QFileInfo(path).filePath();
        }
    }

    if (xml.hasError()) {
        qWarning() << "XML error:" << xml.errorString();
    }

    file.close();
    return typeToFilePath;
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

    std::unordered_map<QString, QString> typeToFilePath = loadTypeToFilePath("../layout/layout.xml");

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
            QString status = element.attribute("status");

            qDebug() << "Element type:" << type << "ID:" << id << "Row:" << row << "Col:" << col;

            auto it = typeToFilePath.find(type);
            if (it == typeToFilePath.end()) {
                qWarning() << "Invalid type:" << type;
                continue;
            }
            QString m_svgFilePath = it->second;

            QFileInfo svgFileInfo(m_svgFilePath);
            if (!svgFileInfo.exists()) {
                qWarning() << "SVG file does not exist at:" << m_svgFilePath;
                continue;
            }

            // Create a temporary file
            QDir dir;
            if (!dir.exists(".tmp")) {
                dir.mkpath(".tmp");
            }
            QString tmpFilePath = QString(".tmp/tmp_%1_%2.svg").arg(type).arg(id);
            QFile tmpFile(tmpFilePath);
            if (!tmpFile.exists()) {
                QFile::copy(m_svgFilePath, tmpFilePath); // Copy the original file to the temporary location
            }

            // Edit the temporary SVG file based on the status
            if (type == "turnout") {
                if (!tmpFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
                    qWarning() << "Failed to open temporary SVG file:" << tmpFilePath;
                    continue;
                }

                QDomDocument svgDoc;
                if (!svgDoc.setContent(&tmpFile)) {
                    qWarning() << "Failed to parse temporary SVG file:" << tmpFilePath;
                    tmpFile.close();
                    continue;
                }

                QDomElement svgRoot = svgDoc.documentElement();
                QDomNodeList paths = svgRoot.elementsByTagName("path");

                for (int k = 0; k < paths.count(); ++k) {
                    QDomElement path = paths.at(k).toElement();
                    QString pathId = path.attribute("id");

                    if (pathId == "_basic") {
                        path.setAttribute("visibility", (status == "S+") ? "visible" : "hidden");
                    } else if (pathId == "_reverse") {
                        path.setAttribute("visibility", (status == "S-") ? "visible" : "hidden");
                    }
                }

                // Update the text element with the turnout ID
                QString modifiedId = id;
                modifiedId.remove('T');
                QDomNodeList texts = svgRoot.elementsByTagName("text");
                for (int k = 0; k < texts.count(); ++k) {
                    QDomElement text = texts.at(k).toElement();
                    if (text.attribute("id") == "_show_id") {
                        text.firstChild().setNodeValue(modifiedId);
                        break;
                    }
                }
                tmpFile.resize(0); // Clear the file content
                QTextStream stream(&tmpFile);
                stream << svgDoc.toString();
                tmpFile.close();
            }

            // Load the temporary SVG file
            auto *svgItem = new SVGHandleEvent(tmpFilePath, id, row, col, flipped, rotate);
            svgItem->setScaleAndPosition(Scale, col * Position_Col, row * Position_Row);

            ApplyTransformation(flipped, rotate, svgItem, type);

            scene->addItem(svgItem);

            qDebug() << "SVG item added at (" << col * Position_Col << "," << row * Position_Row << ")";
        }
    }
}

void StationControl::ApplyTransformation(bool flipped, int rotate, SVGHandleEvent *svgItem, const QString& m_type) {
    QString transformStr;

    if(m_type == "turnout"){
        if (rotate == 0) {
            if (flipped) {
                transformStr = "scale(-1, 1) translate(-8,0) rotate(0)"; //vymenit 0 za 1
            } else {
                transformStr = "scale(1, 1) translate(0,0) rotate(0)"; //vymenit 0 za 1
            }
        } else if (rotate == 180) {
            if (flipped) {
                transformStr = "scale(-1, 1) translate(0,12) rotate(180)"; //ok
            } else {
                transformStr = "scale(1, 1) translate(8,12) rotate(180)"; //ok
            }
        }
    }

    svgItem->updateTransform(transformStr);
}