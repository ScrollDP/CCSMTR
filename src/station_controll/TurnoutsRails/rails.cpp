#include <QGraphicsScene>
#include "rails.h"
#include <QtXml/QDomDocument>
#include <QFile>
#include <QDir>
#include <QXmlStreamAttributes>


rails::rails() {
    setupScene();
    loadFromXml("turnouts.xml");
}

rails::~rails() {
    delete railsSceneGraphic;
}


void rails::setupScene() {



    //horna lava cast
    //initial rail
    addLine(0, 0, 120, 0, Qt::darkGray);

    //under 45 degree and 80 pixels long and make end longer by 20 pixels
    QString xml = turnoutToXml(120, 0, QColor("red"), 0, 0, 0, 0);
    saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(120, 0, Qt::yellow, 0, 1, 0, 0);
    //under 45 degree and 40 pixels long
    xml = turnoutToXml(120, 80, Qt::blue, 0, 0, 1, 0);
    saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(120, 80, Qt::yellow, 0, 1, 1, 0);
    //turnout like this: addLineToScene(160, 40, 200, 0, Qt::red);
    xml = turnoutToXml(280, 80, Qt::red, 0, 0, 0, 1);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(280, 80, Qt::yellow, 0, 1, 0, 1);
    //turnout opsite of addLineWithTurn(120, 0, 160, 40, Qt::red, 20, 0);
    xml = turnoutToXml(280, 0, Qt::blue, 0, 0, 1, 1);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //xml = turnoutToXmlppp(280, 0, Qt::yellow, 0, 1, 1, 1);



    //turnout Left 40 pixels long 45 degree north
    xml = turnoutToXml(280, 0, Qt::green, 0, 0, 1, 0);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //xml = turnoutToXmlppp(280, 0, Qt::yellow, 0, 1, 1, 0);

    //turnout Left 45 degree north after this: addLineWithTurn(280, 0, 240, 40, Qt::green, 0, 180);
    xml = turnoutToXml(360, -40, Qt::darkCyan, 315, 0, 1, 0);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch straight line
        //addTurnoutToScene(360, -40, Qt::yellow, 315, 1, 1, 0);
    //turnout right after imaginary line
    xml = turnoutToXml(440, -120, Qt::green, 315, 0, 0, 0);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(440, -120, Qt::yellow, 315, 1, 0, 0);
    //add straight line 40 pixels long after turnout
    addLine(520, -200, 560, -240, Qt::darkGray); //kolaj obluk ku kolaji 6

    //straight line 40 pixels long afterdarkCyan turnout
    addLine(400, -120, 400, -160, Qt::darkGray);
    //straight line
    addLine(400, -160, 560, -320, Qt::darkGray); //obluk ku kolaji 8
    //straight line
    addLine(560, -320, 1260, -320, Qt::darkGray); //kolaj 8


    //straight line 40 pixels long
    addLine(560, -240, 1220, -240, Qt::darkGray); //kolaj 6

    //straight line 40 pixels long
    addLine(520, -160, 1260, -160, Qt::darkGray); //kolaj 4

    //rail 360 pixels long straight
    addLine(360, 0, 1420, 0, Qt::darkGray); //kolaj 2

    //horna prava cast
    //straight line medzi turnout horna a cross turnout
    addLine(1500,0,1580,0,Qt::darkGray);
    //turnout horna main
    xml = turnoutToXml(1500, 0, Qt::green, 180, 0, 0, 0);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(1500, 0, Qt::yellow, 180, 1, 0, 0);
    //straight rail kolaj 4-5 ->lietavska lucka
    addLine(1420, -40, 1340, -120, Qt::darkGray); //kolaj 4-5 lietavska lucka
    //turnout cross
    xml = turnoutToXml(1340, -120, Qt::darkCyan, 225, 0, 1, 0);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(1340, -120, Qt::yellow, 225, 1, 1, 0);
    //turnout from other side
    xml = turnoutToXml(1260, -200, Qt::green, 45, 0, 1, 0);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(1260, -200, Qt::yellow, 45, 1, 1, 0);
    //straight rail kolaj 6 obluk
    addLine(1260, -200, 1220, -240, Qt::darkGray); //kolaj 6 obluk
    //straight rail lietavska lucka
    addLine(1340, -160, 1420, -160, Qt::darkGray); //kolaj 6 lietavska lucka
    //turnout default lietavska lucka
    xml = turnoutToXml(1500, -160, Qt::green, 180, 0, 0, 0);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(1500, -160, Qt::yellow, 180, 1, 0, 0);
    //kolaj lietavska lucka
    addLine(1500, -160, 1860, -160, Qt::darkGray); //kolaj lietavska lucka
    //kolaj obluk ku kolaji 8
    addLine(1420, -200, 1340, -280, Qt::darkGray); //kolaj obluk ku kolaji 8
    //turnout cross kolaj 8 a depo
    xml = turnoutToXml(1340, -280, Qt::darkCyan, 225, 0, 1, 0);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(1340, -280, Qt::yellow, 225, 1, 1, 0);
    //turnout from other side
    xml = turnoutToXml(1260, -360, Qt::green, 45, 0, 1, 0);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(1260, -360, Qt::yellow, 45, 1, 1, 0);
    //kolaj depo
    addLine(1340, -320, 1600, -320, Qt::darkGray); //kolaj depo
    //kolaj na kolaj 10 a 12
    addLine(1260, -360, 1220 ,-400, Qt::darkGray); //kolaj na kolaj 10 a 12
    //turnout  kolaj 10 a 12
    xml = turnoutToXml(1220, -400, Qt::green, 225, 0, 1, 0);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(1220, -400, Qt::yellow, 225, 1, 1, 0);
    //kolaj 10
    addLine(1140, -440, 980, -440, Qt::darkGray); //kolaj 10
    //kolaj 12 obluk
    addLine(1140, -480, 1100, -520, Qt::darkGray); //kolaj 12 obluk
    //kolaj 12
    addLine(1100, -520, 980, -520, Qt::darkGray); //kolaj 12



    //dolna lava cast
    //initial rail under first one
    addLine(0, 80, 120, 80, Qt::darkGray);
    //straight line
    addLine(360, 80, 1420, 80, Qt::darkGray); //kolaj 1
    //turnout line position start at 280
    xml = turnoutToXml(280, 80, Qt::green, 0, 0, 0, 0);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(280, 80, Qt::yellow, 0, 1, 0, 0);
    //straight line under 45 degree
    addLine(360, 120, 440, 200, Qt::darkGray);
    //turnout left starting point 440,200
    xml = turnoutToXml(440, 200, Qt::green, 45, 0, 1, 0);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(440, 200, Qt::yellow, 45, 1, 1, 0);
    //straight rail kolaj 3
    addLine(520, 240, 1300, 240, Qt::darkGray); //kolaj 3

    //turnout left
    xml = turnoutToXml(520, 280, Qt::green, 45, 0, 1, 0);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(520, 280, Qt::yellow, 45, 1, 1, 0);
    //cross turnout
    xml = turnoutToXml(600, 360, Qt::darkCyan, 225, 0, 1, 0);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(600, 360, Qt::yellow, 225, 1, 1, 0);
    //turnout continue straight
    xml = turnoutToXml(680, 440, Qt::green, 225, 0, 1, 0);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(680, 440, Qt::yellow, 225, 1, 1, 0);
    //turnout to odbocka
    xml = turnoutToXml(600, 400, Qt::green, 180, 0, 1, 0);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(600, 400, Qt::yellow, 180, 1, 1, 0);
    //straight rail
    addLine(680, 320, 1260, 320, Qt::darkGray); //kolaj 5
    //turnout ku kolaji 5 a 7
    xml = turnoutToXml(600, 320, Qt::green, 0, 0, 0, 0);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(600, 320, Qt::yellow, 0, 1, 0, 0);
    //straight rail kolaj 7 obluk
    addLine(680, 360, 720,400, Qt::darkGray); //kolaj 7 obluk
    //straight rail kolaj 7
    addLine(720, 400, 1180, 400, Qt::darkGray); //kolaj 7

    //straight rail
    addLine(680,440,720,480,Qt::darkGray); //kolaj 9 obluk
    //straight rail
    addLine(720,480,1140,480,Qt::darkGray); //kolaj 9

    //straight rail odbočka
    addLine(520, 320, 0, 320, Qt::darkGray);
    addLine(520, 400, 80, 400, Qt::darkGray);
    //obluk
    addLine(520, 440, 480, 480, Qt::darkGray);
    addLine(480, 480, 80, 480, Qt::darkGray);





    //dolna prava cat
    //initial rail
    addLine(1740, 80, 1860, 80, Qt::darkGray);
//initial rail
    addLine(1740, 0, 1860, 0, Qt::darkGray);

    //turnout opsite of addLineWithTurn(120, 0, 160, 40, Qt::red, 20, 0);
    xml = turnoutToXml(1740, 0, Qt::blue, 0, 0, 1, 1);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(1740, 0, Qt::yellow, 0, 1, 1, 1);
    //under 45 degree and 80 pixels long and make end longer by 20 pixels
    xml = turnoutToXml(1580, 0, Qt::red, 0, 0, 0, 0);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(1580, 0, Qt::yellow, 0, 1, 0, 0);
    //under 45 degree and 40 pixels long
    xml = turnoutToXml(1580, 80, Qt::blue, 0, 0, 1, 0);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(1580, 80, Qt::yellow, 0, 1, 1, 0);
    //turnout like this: addLineToScene(160, 40, 200, 0, Qt::red);
    xml = turnoutToXml(1740, 80, Qt::red, 0, 0, 0, 1);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(1740, 80, Qt::yellow, 0, 1, 0, 1);



    //turnout first from cross turnout
    xml = turnoutToXml(1580, 80, Qt::green, 180, 0, 1, 0);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(1580, 80, Qt::yellow, 180, 1, 1, 0);
    //same turnout after that
    xml = turnoutToXml(1500, 80, Qt::darkCyan, 180, 0, 1, 0);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(1500, 80, Qt::yellow, 180, 1, 1, 0);

    //straight rail obluk kolaj 3
    addLine(1420, 120, 1300, 240, Qt::darkGray); //kolaj 3 obluk
    //straight rail obluk turnout ku kolaji 5,7,9
    addLine(1500, 120, 1340, 280, Qt::darkGray); //kolaj obluk ku kolaji 5,7,9
    //turnout
    xml = turnoutToXml(1340, 280, Qt::green, 135, 0, 0, 0);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(1340, 280, Qt::yellow, 135, 1, 0, 0);
    //turnout ANG
    xml = turnoutToXml(1260, 360, Qt::darkCyan, 135, 0, 0, 0);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(1260, 360, Qt::yellow, 135, 1, 0, 0);
    //turnout ANG2
    xml = turnoutToXml(1180, 440, Qt::green, 315, 0, 0, 0);saveToXml("turnouts.xml", xml);
    //imaginary turnout switch
        //addTurnoutToScene(1180, 440, Qt::yellow, 315, 1, 0, 0);
    //straight rail from ang2
    addLine(1260, 400, 1580, 400, Qt::darkGray); //odstavna
    //straight rail from ang2 rail 9 obluk
    addLine(1180, 440, 1140, 480, Qt::darkGray); //kolaj 9 obluk




}

void rails::addTurnoutToScene(int x1, int y1, QColor color, double angleTurnout, bool switchTurnout, bool flipped, bool mirror) {
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
    addLine(x1, y1, x1_initial, y1_initial, Qt::darkMagenta);

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
    addLine(x1_initial, y1_initial, x2, y2, color);

    // Add the turnout item

    // Add the turnout item
    auto *turnout = new CustomTurnoutItem(x1, y1, x1_initial, y1_initial);

    // Connect the turnoutClicked signal to a lambda function that updates switchTurnout
    connect(turnout, &CustomTurnoutItem::turnoutClicked, [&]() {
        switchTurnout = !switchTurnout;
        qDebug() << "Turnout switch state is now: " << (switchTurnout ? "ON" : "OFF");
    });

    railsSceneGraphic->addItem(turnout);

    switchTurnout = !switchTurnout;

}



void rails::addLine(int x1, int y1, int x2, int y2, QColor color) const {
    auto *line = new CustomLineItem(x1, y1, x2, y2);

    if (color == Qt::yellow){
        line->setPen(QPen(color, 3, Qt::SolidLine, Qt::MPenCapStyle, Qt::MPenJoinStyle));
        line->setZValue(1);
    } else {
        line->setPen(QPen(color, 10, Qt::SolidLine, Qt::MPenCapStyle, Qt::MPenJoinStyle));
        line->setZValue(0);
    }
    railsSceneGraphic->addItem(line);
}



void rails::loadFromXml(const QString& fileName) {
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

                addTurnoutToScene(startX, startY, color, angleTurnout, switchTurnout, flipped, mirror);
                qDebug() << "Turnout added: " << id << " " << startX << " " << startY << " " << color.name() << " " << angleTurnout << " " << switchTurnout << " " << flipped << " " << mirror;
            }
        }
    }

    if (xmlReader.hasError()) {
        qDebug() << "Error parsing XML file: " << xmlReader.errorString();
    }

    file.close();
}

QString rails::turnoutToXml(int startX, int startY, QColor color, double angleTurnout, bool switchTurnout, bool flipped, bool mirror) {
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

void rails::saveToXml(const QString& fileName, const QString& xmlString) {
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