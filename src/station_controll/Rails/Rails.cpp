#include <QGraphicsScene>
#include "Rails.h"
#include <QtXml/QDomDocument>
#include <QFile>
#include <QDir>
#include <QXmlStreamAttributes>
#include <QSpinBox>
#include <QGraphicsProxyWidget>


Rails::Rails() {
    loadFromXmlRails();
    loadFromXmlTurnouts(idLoad, fileName);
}

Rails::~Rails() {
    delete railsSceneGraphic;
}

const QString Rails::fileName = "turnouts.xml";


void Rails::addTurnoutToScene(int idLine, int x1, int y1, QColor color, double angleTurnout, bool switchTurnout, bool flipped, bool mirror) {
     // Convert angleTurnout from degrees to radians
    double angleTurnoutRad = angleTurnout * M_PI / 180;

    // Calculate the length of the first line
    double length1 = 40;
    if (angleTurnout == 45 || angleTurnout == 135 || angleTurnout == 225 || angleTurnout == 315) {
        length1 = sqrt(3200);
    }

    // Calculate the initial position of the first line
    int x1_initial, y1_initial;
    if (mirror) {
        x1_initial = x1 - length1 * cos(angleTurnoutRad);
        y1_initial = y1 - length1 * sin(angleTurnoutRad);
    } else {
        x1_initial = x1 + length1 * cos(angleTurnoutRad);
        y1_initial = y1 + length1 * sin(angleTurnoutRad);
    }

    // First part of the line: straight until the turn
    addLine(x1, y1, x1_initial, y1_initial, Qt::darkMagenta, idLine, switchTurnout);

    // Calculate the direction of the first line segment
    double direction = angleTurnoutRad;

    // Calculate the new direction after the turn
    double newDirection;
    double length2 = 40;
    if (switchTurnout) {
        // If the turnout will switch, the second half will be straight
        newDirection = direction;
    } else if (flipped) {
        // If the turnout will be flipped, the default angle will be -45 degrees
        newDirection = direction - M_PI / 4;

    } else {
        // Otherwise, the default angle will be 45 degrees
        newDirection = direction + M_PI / 4;
    }

    // Calculate the length of the second line
    if (fabs(newDirection) == M_PI / 4 || fabs(newDirection) == 3 * M_PI / 4 || fabs(newDirection) == 5 * M_PI / 4 || fabs(newDirection) == 7 * M_PI / 4) {
        length2 = sqrt(3200);
        //qDebug() << "length2: " << length2;
    }

    // Calculate the end point of the second line segment
    int x2, y2;
    if (mirror) {
        x2 = x1_initial - length2 * cos(newDirection);
        y2 = y1_initial - length2 * sin(newDirection);
    } else {
        x2 = x1_initial + length2 * cos(newDirection);
        y2 = y1_initial + length2 * sin(newDirection);
    }
        // Second part of the line: after the turn
        addLine(x1_initial, y1_initial, x2, y2, color, idLine, switchTurnout);
}


void Rails::addLine(int x1, int y1, int x2, int y2, QColor color, int idLine, bool switchTurnout) {
    auto *line = new RailsAction(x1, y1, x2, y2, idLine, switchTurnout, this);

    line->setPen(QPen(color, 10, Qt::SolidLine, Qt::MPenCapStyle, Qt::MPenJoinStyle));
    line->setZValue(0);
    railsSceneGraphic->addItem(line);
}



bool Rails::loadFromXmlTurnouts(int m_idLine, const QString& string) {

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening file: " << fileName;
    }

    QXmlStreamReader xmlReader(&file);
    int startX, startY;
    QColor color;
    double angleTurnout;
    bool switchTurnout, flipped, mirror;

    while (!xmlReader.atEnd()) {
        xmlReader.readNext();
        if (xmlReader.isStartElement()) {
            if (xmlReader.name().toString() == "turnout") {

                QXmlStreamAttributes attributes = xmlReader.attributes();
                int idLine = attributes.value("id").toInt();


                // Skip this turnout if its idLine doesn't match the idLine parameter
                if (!firstLoad && m_idLine != idLine) {
                    //qDebug() << "Skipping turnout with idLine: " << idLine;
                    continue;
                }

                xmlReader.readNextStartElement();
                if (xmlReader.name().toString() == "start") {
                    attributes = xmlReader.attributes();
                    startX = attributes.value("x").toInt();
                    startY = attributes.value("y").toInt();
                    xmlReader.readNext();
                }

                xmlReader.readNextStartElement();
                if (xmlReader.name().toString() == "color") {
                    color = QColor(xmlReader.readElementText());
                }

                xmlReader.readNextStartElement();
                if (xmlReader.name().toString() == "angleTurnout") {
                    angleTurnout = xmlReader.readElementText().toDouble();
                }

                xmlReader.readNextStartElement();
                if (xmlReader.name().toString() == "switchTurnout") {
                    switchTurnout = xmlReader.readElementText().toInt();
                }

                xmlReader.readNextStartElement();
                if (xmlReader.name().toString() == "flipped") {
                    flipped = xmlReader.readElementText().toInt();
                }

                xmlReader.readNextStartElement();
                if (xmlReader.name().toString() == "mirror") {
                    mirror = xmlReader.readElementText().toInt();
                }

                addTurnoutToScene(idLine, startX, startY, color, angleTurnout, switchTurnout, flipped, mirror);
                //qDebug() << "Turnout added: " << idLine << " " << startX << " " << startY << " " << color.name() << " " << angleTurnout << " " << switchTurnout << " " << flipped << " " << mirror;
            }
        }

    }

    if (xmlReader.hasError()) {
        qDebug() << "Error parsing XML file: " << xmlReader.errorString();
    }

    file.close();

    firstLoad = false;
    return switchTurnout;
}

bool Rails::updateTurnoutInXml(int idLine, bool switchTurnout) {

    QFile file(fileName); // Replace with your XML file name
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Error opening file for writing: " << file.fileName();

    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qDebug() << "Error parsing XML file: " << file.fileName();

    }
    file.close();

    QDomElement root = doc.firstChildElement("turnouts");
    QDomNodeList turnoutList = root.elementsByTagName("turnout");
    for (int i = 0; i < turnoutList.size(); ++i) {
        QDomElement turnoutElement = turnoutList.at(i).toElement();
        if (turnoutElement.attribute("id").toInt() == idLine) {
            QDomElement switchElement = turnoutElement.firstChildElement("switchTurnout");
            switchElement.firstChild().setNodeValue(switchTurnout ? "1" : "0");
            break;
        }
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error opening file for writing: " << file.fileName();

    }
    QTextStream stream(&file);
    stream << doc.toString();

    file.close();

    return switchTurnout;
}

void Rails::deleteLinesWithId(int idLine) const {
    QList<QGraphicsItem*> allItems = railsSceneGraphic->items();
    for (QGraphicsItem* item : allItems) {
        if (auto* line = dynamic_cast<RailsAction*>(item)) {
            if (line->getTurnoutId() == idLine) {
                railsSceneGraphic->removeItem(line);
                delete line;
            }
        }
    }
}

bool Rails::loadFromXmlRails() {
    QFile file("rails.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening file: " << file.fileName();
        return false;
    }

    QXmlStreamReader xmlReader(&file);
    int x1, y1, x2, y2, idLine;
    QColor color;
    bool switchTurnout;

    while (!xmlReader.atEnd()) {
        xmlReader.readNext();
        if (xmlReader.isStartElement()) {
            if (xmlReader.name().toString() == "rail") {
                QXmlStreamAttributes attributes = xmlReader.attributes();
                x1 = attributes.value("x1").toInt();
                y1 = attributes.value("y1").toInt();
                x2 = attributes.value("x2").toInt();
                y2 = attributes.value("y2").toInt();
                color = QColor(attributes.value("color").toString());
                idLine = attributes.value("idLine").toInt();
                switchTurnout = attributes.value("switchTurnout").toString() == "true";

                addLine(x1, y1, x2, y2, color, idLine, switchTurnout);
            }
        }
    }

    if (xmlReader.hasError()) {
        qDebug() << "Error parsing XML file: " << xmlReader.errorString();
        return false;
    }

    file.close();
    return true;
}
