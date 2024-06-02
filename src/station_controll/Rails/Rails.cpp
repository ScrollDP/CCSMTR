#include <QGraphicsScene>
#include "Rails.h"
#include <QtXml/QDomDocument>
#include <QFile>
#include <QDir>
#include <QXmlStreamAttributes>
#include <QSpinBox>
#include <QGraphicsProxyWidget>


Rails::Rails() {
    setupScene();
    loadFromXml(id,"turnouts.xml");
}

Rails::~Rails() {
    delete railsSceneGraphic;
}

int Rails::id = 0;


void Rails::setupScene() {


    //horna lava cast
    //initial rail
    addLine(0, 0, 120, 0, Qt::darkGray,0,0);
    //add straight line 40 pixels long after turnout
    addLine(520, -200, 560, -240, Qt::darkGray,0,0); //kolaj obluk ku kolaji 6
    //straight line 40 pixels long afterdarkCyan turnout
    addLine(400, -120, 400, -160, Qt::darkGray,0,0);
    //straight line
    addLine(400, -160, 560, -320, Qt::darkGray,0,0); //obluk ku kolaji 8
    //straight line
    addLine(560, -320, 1260, -320, Qt::darkGray,0,0); //kolaj 8
    //straight line 40 pixels long
    addLine(560, -240, 1220, -240, Qt::darkGray,0,0); //kolaj 6
    //straight line 40 pixels long
    addLine(520, -160, 1260, -160, Qt::darkGray,0,0); //kolaj 4
    //rail 360 pixels long straight
    addLine(360, 0, 1420, 0, Qt::darkGray,0,0); //kolaj 2


    //horna prava cast
    //straight line medzi turnout horna a cross turnout
    addLine(1500,0,1580,0,Qt::darkGray,0,0);
    //straight rail kolaj 4-5 ->lietavska lucka
    addLine(1420, -40, 1340, -120, Qt::darkGray,0,0); //kolaj 4-5 lietavska lucka
    //straight rail kolaj 6 obluk
    addLine(1260, -200, 1220, -240, Qt::darkGray,0,0); //kolaj 6 obluk
    //straight rail lietavska lucka
    addLine(1340, -160, 1420, -160, Qt::darkGray,0,0); //kolaj 6 lietavska lucka
    //kolaj lietavska lucka
    addLine(1500, -160, 1860, -160, Qt::darkGray,0,0); //kolaj lietavska lucka
    //kolaj obluk ku kolaji 8
    addLine(1420, -200, 1340, -280, Qt::darkGray,0,0); //kolaj obluk ku kolaji 8
    //kolaj depo
    addLine(1340, -320, 1600, -320, Qt::darkGray,0,0); //kolaj depo
    //kolaj na kolaj 10 a 12
    addLine(1260, -360, 1220 ,-400, Qt::darkGray,0,0); //kolaj na kolaj 10 a 12
    //kolaj 10
    addLine(1140, -440, 980, -440, Qt::darkGray,0,0); //kolaj 10
    //kolaj 12 obluk
    addLine(1140, -480, 1100, -520, Qt::darkGray,0,0); //kolaj 12 obluk
    //kolaj 12
    addLine(1100, -520, 980, -520, Qt::darkGray,0,0); //kolaj 12


    //dolna lava cast
    //initial rail under first one
    addLine(0, 80, 120, 80, Qt::darkGray,0,0);
    //straight line
    addLine(360, 80, 1420, 80, Qt::darkGray,0,0); //kolaj 1
    //straight line under 45 degree
    addLine(360, 120, 440, 200, Qt::darkGray,0,0);
    //turnout left starting point 440,200
    //straight rail kolaj 3
    addLine(520, 240, 1300, 240, Qt::darkGray,0,0); //kolaj 3
    //straight rail
    addLine(680, 320, 1260, 320, Qt::darkGray,0,0); //kolaj 5
    //turnout ku kolaji 5 a 7
    //straight rail kolaj 7 obluk
    addLine(680, 360, 720,400, Qt::darkGray,0,0); //kolaj 7 obluk
    //straight rail kolaj 7
    addLine(720, 400, 1180, 400, Qt::darkGray,0,0); //kolaj 7
    //straight rail
    addLine(680,440,720,480,Qt::darkGray,0,0); //kolaj 9 obluk
    //straight rail
    addLine(720,480,1140,480,Qt::darkGray,0,0); //kolaj 9
    //straight rail odbočka
    addLine(520, 320, 0, 320, Qt::darkGray,0,0);
    addLine(520, 400, 80, 400, Qt::darkGray,0,0);
    //obluk
    addLine(520, 440, 480, 480, Qt::darkGray,0,0);
    addLine(480, 480, 80, 480, Qt::darkGray,0,0);

    //dolna prava cat
    //initial rail
    addLine(1740, 80, 1860, 80, Qt::darkGray,0,0);
    //initial rail
    addLine(1740, 0, 1860, 0, Qt::darkGray,0,0);
    //straight rail obluk kolaj 3
    addLine(1420, 120, 1300, 240, Qt::darkGray,0,0); //kolaj 3 obluk
    //straight rail obluk turnout ku kolaji 5,7,9
    addLine(1500, 120, 1340, 280, Qt::darkGray,0,0); //kolaj obluk ku kolaji 5,7,9
    //straight rail from ang2
    addLine(1260, 400, 1580, 400, Qt::darkGray,0,0); //odstavna
    //straight rail from ang2 rail 9 obluk
    addLine(1180, 440, 1140, 480, Qt::darkGray,0,0); //kolaj 9 obluk
}

void Rails::addTurnoutToScene(int id, int x1, int y1, QColor color, double angleTurnout, bool switchTurnout, bool flipped, bool mirror) {
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
    addLine(x1, y1, x1_initial, y1_initial, Qt::darkMagenta, id, switchTurnout);

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
    addLine(x1_initial, y1_initial, x2, y2, color, id, switchTurnout);

}



void Rails::addLine(int x1, int y1, int x2, int y2, QColor color, int turnoutId, bool switchTurnout) {
    auto *line = new RailsAction(x1, y1, x2, y2, turnoutId, switchTurnout, this);
    if (!turnoutGroups.contains(turnoutId)) {
        turnoutGroups[turnoutId] = new QGraphicsItemGroup();
    }
    turnoutGroups[turnoutId]->addToGroup(line);

    if (color == Qt::yellow){
        line->setPen(QPen(color, 3, Qt::SolidLine, Qt::MPenCapStyle, Qt::MPenJoinStyle));
        line->setZValue(1);
    } else {
        line->setPen(QPen(color, 10, Qt::SolidLine, Qt::MPenCapStyle, Qt::MPenJoinStyle));
        line->setZValue(0);
    }
    railsSceneGraphic->addItem(line);
}



void Rails::loadFromXml(int turnoutId, const QString& fileName) {

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening file: " << fileName;
        return;
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
                int id = attributes.value("id").toInt();


                // Skip this turnout if its id doesn't match the id parameter
                if (!firstLoad && turnoutId != id) {
                    //qDebug() << "Skipping turnout with id: " << id;
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

                addTurnoutToScene(id, startX, startY, color, angleTurnout, switchTurnout, flipped, mirror);
                //qDebug() << "Turnout added: " << id << " " << startX << " " << startY << " " << color.name() << " " << angleTurnout << " " << switchTurnout << " " << flipped << " " << mirror;
            }
        }

    }

    if (xmlReader.hasError()) {
        qDebug() << "Error parsing XML file: " << xmlReader.errorString();
    }

    file.close();

    firstLoad = false;
}

QString Rails::turnoutToXml(int startX, int startY, QColor color, double angleTurnout, bool switchTurnout, bool flipped, bool mirror) {
    static int uniqueId = 1; // This will be incremented for each turnout

    QDomDocument doc;
    QDomElement turnoutElement = doc.createElement("turnout");
    turnoutElement.setAttribute("id", uniqueId++); // Use and increment the unique ID

    QDomElement startElement = doc.createElement("start");
    startElement.setAttribute("x", startX);
    startElement.setAttribute("y", startY);
    turnoutElement.appendChild(startElement);

    QDomElement colorElement = doc.createElement("color");
    QDomText colorText = doc.createTextNode(color.name());
    colorElement.appendChild(colorText);
    turnoutElement.appendChild(colorElement);

    QDomElement angleElement = doc.createElement("angleTurnout");
    QDomText angleText = doc.createTextNode(QString::number(angleTurnout));
    angleElement.appendChild(angleText);
    turnoutElement.appendChild(angleElement);

    QDomElement switchElement = doc.createElement("switchTurnout");
    QDomText switchText = doc.createTextNode(switchTurnout ? "1" : "0");
    switchElement.appendChild(switchText);
    turnoutElement.appendChild(switchElement);

    QDomElement flippedElement = doc.createElement("flipped");
    QDomText flippedText = doc.createTextNode(flipped ? "1" : "0");
    flippedElement.appendChild(flippedText);
    turnoutElement.appendChild(flippedElement);

    QDomElement mirrorElement = doc.createElement("mirror");
    QDomText mirrorText = doc.createTextNode(mirror ? "1" : "0");
    mirrorElement.appendChild(mirrorText);
    turnoutElement.appendChild(mirrorElement);

    // Add the address element
    QDomElement addressElement = doc.createElement("address");
    QDomText addressText = doc.createTextNode("5"); // Fixed address value
    addressElement.appendChild(addressText);
    turnoutElement.appendChild(addressElement);

    doc.appendChild(turnoutElement);

    return doc.toString();
}

void Rails::saveToXml(const QString& fileName, const QString& xmlString) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Error opening file for writing: " << fileName;
        return;
    }

    // Read the existing XML from the file
    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qDebug() << "Error parsing XML file: " << fileName;
        return;
    }
    file.close();

    // Parse the new turnout XML
    QDomDocument newTurnoutDoc;
    newTurnoutDoc.setContent(xmlString);
    QDomElement newTurnoutElement = newTurnoutDoc.firstChildElement("turnout");

    // Append the new turnout to the root element of the existing XML
    QDomElement root = doc.firstChildElement("turnouts");
    root.appendChild(newTurnoutElement);

    // Write the updated XML back to the file
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error opening file for writing: " << fileName;
        return;
    }
    QTextStream stream(&file);
    stream << doc.toString();

    file.close();
}

bool Rails::updateTurnoutInXml(int id, bool switchTurnout) {
    QFile file("turnouts.xml"); // Replace with your XML file name
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
        if (turnoutElement.attribute("id").toInt() == id) {
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


