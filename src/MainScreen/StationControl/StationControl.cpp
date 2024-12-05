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

            // Create a svg temporary file
            QDir dir;
            if (!dir.exists(".tmp/svgFiles")) {
                dir.mkpath(".tmp/svgFiles");
            }
            QString tmpFilePath = QString(".tmp/svgFiles/tmp_%1_%2.svg").arg(type).arg(id);
            if (!QFile::exists(tmpFilePath)) {
                QFile::copy(m_svgFilePath, tmpFilePath); // Copy the original file to the temporary location
            }

            // Create config file if it does not exist
            if(type == "turnout" || type == "ang_turnout") {
                QString configFilePath = QString(".tmp/svgConfigFiles/%1.xml").arg(id);
                if (!QFile::exists(configFilePath) && id.startsWith("T")) {
                    createTurnoutConfigFile(configFilePath, "S-", type); // Default status
                }
                else if(!QFile::exists(configFilePath) && id.startsWith("AT")) {
                    createTurnoutConfigFile(configFilePath, "S+-", type); // Default status
                }
            }

            // Load status from the turnout config file
            QString status = loadTurnoutStatusFromConfigFile(id);

            // Edit the temporary SVG file based on the status
            if (type == "turnout" || type == "ang_turnout") {
                QFile tmpFile(tmpFilePath);
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

            // Create SVG file (existing code)
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
    if(m_type == "ang_turnout"){
        if (rotate == 0) {
            if (flipped) {
                transformStr = "scale(-1, 1) translate(-16,0) rotate(0)"; //vymenit 0 za 1
            } else {
                transformStr = "scale(1, 1) translate(0,0) rotate(0)"; //vymenit 0 za 1
            }
        }
    }

    svgItem->updateTransform(transformStr);
}

// Function to create the configuration XML file for a turnout
void StationControl::createTurnoutConfigFile(const QString &filePath, const QString &status, const QString &type) {
    // Check if the file already exists
    QFile file(filePath);
    if (file.exists()) {
        qDebug() << "Config file already exists:" << filePath;
        return;
    }

    QDomDocument doc;
    QDomElement root = doc.createElement("turnoutConfig");
    doc.appendChild(root);
    if(type == "turnout") {
        QDomElement basicElement = doc.createElement("_basic");
        QDomText basicInt = doc.createTextNode("1");
        basicElement.appendChild(basicInt);
        root.appendChild(basicElement);

        QDomElement reverseElement = doc.createElement("_reverse");
        QDomText reverseInt = doc.createTextNode("0");
        reverseElement.appendChild(reverseInt);
        root.appendChild(reverseElement);

        QDomElement statusElement = doc.createElement("status");
        QDomText statusText = doc.createTextNode(status);
        statusElement.appendChild(statusText);
        root.appendChild(statusElement);
    }
    else if (type == "ang_turnout") {
        QDomElement id1Element = doc.createElement("id1");
        QDomElement basicElement1 = doc.createElement("_basic");
        QDomText basicInt1 = doc.createTextNode("0");
        basicElement1.appendChild(basicInt1);
        id1Element.appendChild(basicElement1);

        QDomElement reverseElement1 = doc.createElement("_reverse");
        QDomText reverseInt1 = doc.createTextNode("1");
        reverseElement1.appendChild(reverseInt1);
        id1Element.appendChild(reverseElement1);
        root.appendChild(id1Element);

        QDomElement id2Element = doc.createElement("id2");
        QDomElement basicElement2 = doc.createElement("_basic");
        QDomText basicInt2 = doc.createTextNode("0");
        basicElement2.appendChild(basicInt2);
        id2Element.appendChild(basicElement2);

        QDomElement reverseElement2 = doc.createElement("_reverse");
        QDomText reverseInt2 = doc.createTextNode("1");
        reverseElement2.appendChild(reverseInt2);
        id2Element.appendChild(reverseElement2);
        root.appendChild(id2Element);

        QDomElement statusElement = doc.createElement("status");
        QDomText statusText = doc.createTextNode(status);
        statusElement.appendChild(statusText);
        root.appendChild(statusElement);
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file for writing:" << filePath;
        return;
    }

    QTextStream stream(&file);
    stream << doc.toString();
    file.close();
}

QString StationControl::loadTurnoutStatusFromConfigFile(const QString &turnoutID) {
    QString configFilePath = QString(".tmp/svgConfigFiles/%1.xml").arg(turnoutID);
    QFile configFile(configFilePath);
    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open turnout config file:" << configFilePath;
        return QString();
    }

    QDomDocument configDoc;
    if (!configDoc.setContent(&configFile)) {
        qWarning() << "Failed to parse turnout config file:" << configFilePath;
        configFile.close();
        return QString();
    }
    configFile.close();

    QDomElement root = configDoc.documentElement();
    QDomElement statusElement = root.firstChildElement("status");
    return statusElement.text();
}

