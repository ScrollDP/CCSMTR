#include "SVGHandleEvent.h"
#include <QGraphicsScene>
#include <QDomDocument>
#include <QRegularExpression>
#include <QGraphicsSceneMouseEvent>
#include <utility>
#include <QMenu>
#include <QTimer>
#include <thread>
#include <mutex>
#include <QDir>


SVGHandleEvent::SVGHandleEvent(const QString &svgFilePath, QString elementId, int row, int col, bool flipped, int rotate, QGraphicsItem* parent)
        : QGraphicsSvgItem(parent),
          svgFilePath(svgFilePath),
          elementId(std::move(elementId)),
          row(row),
          col(col),
          flipped(flipped),
          rotate(rotate),
          renderer(new QSvgRenderer(svgFilePath)){
    if (!renderer->isValid()) {
        qWarning() << "Failed to load SVG file:" << svgFilePath;
        delete renderer;
        renderer = nullptr;
        return;
    }
    this->setSharedRenderer(renderer);

}
SVGHandleEvent::~SVGHandleEvent() {
    if (vyhybkaThread.joinable()) {
        vyhybkaThread.join();
    }
}

void SVGHandleEvent::sendToArduino(const QString &dataList) {
    //qDebug() << "Adding command to queue: " << dataList;
    commandQueue.enqueue(dataList);
}

void SVGHandleEvent::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsSvgItem::mousePressEvent(event);


    if(event->button() == Qt::LeftButton) {
        qDebug() << "Element ID:" << elementId << "|Row:" << row <<"|Col:" << col <<
                 "|Flipped:" << flipped << "|Rotate:" << rotate << "|File:" << svgFilePath;
        if (QRegularExpression("^HN\\d+$").match(elementId).hasMatch()) {
            vlakovaCestaRoute();
        }
        checkIDwithEndpoint(elementId);

    }
    if(event->button() == Qt::MiddleButton) {
        if (QRegularExpression("^HN\\d+$").match(elementId).hasMatch()) {
            hlavneNavestidloMenu(event->screenPos(), elementId);
        }
        else if(QRegularExpression("^T\\d+?$").match(elementId).hasMatch()) {
            vyhybkaMenu(event->screenPos(), elementId);
        }
        else if(QRegularExpression("^ZN\\d+$").match(elementId).hasMatch()) {
            zriadovacieNavestidloMenu(event->screenPos(), elementId);
        }
    }
    if(event->button() == Qt::RightButton) {

    }
}

void SVGHandleEvent::threadToggleVyhybka(bool straight, bool diverging, const QString &path, const QString &elementId) {
    if (vyhybkaThread.joinable()) {
        vyhybkaThread.join();
    }
    vyhybkaThread = std::thread(&SVGHandleEvent::toggleVisibility, this, straight, diverging, path, elementId);
}

void SVGHandleEvent::setScaleAndPosition(qreal scale, qreal x, qreal y) {
    this->setScale(scale);
    this->setPos(x * scale, y * scale);
}

void SVGHandleEvent::changeColorbackground(const QString &path, const QString &elemID) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open SVG file:" << path;
        return;
    }

    QDomDocument adoc;
    if (!adoc.setContent(&file)) {
        qWarning() << "Failed to parse SVG file:" << path;
        file.close();
        return;
    }
    file.close();

    QDomElement aroot = adoc.documentElement();
    QDomNodeList elements = aroot.elementsByTagName("g");

    for (int i = 0; i < elements.count(); ++i) {
        QDomElement element = elements.at(i).toElement();
        if (element.isNull()) {
            continue;
        }
        QString Id = element.attribute("id");

        if (Id == "back_color") {
            element.setAttribute("visibility", "visible");
            //qDebug() << "color changing";
        }
    }

    // Save the changes back to the SVG file
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open SVG file for writing:" << path;
        return;
    }

    QTextStream stream(&file);
    stream << adoc.toString();
    file.close();

    // Reload the SVG to apply changes
    reloadSVG(path,elemID);
}


QString SVGHandleEvent::getElementIdAtPosition(const QPointF &position) {
    QStringList elementIds = getElementIdsFromSvg(QString());
    for ([[maybe_unused]] const QString &id : elementIds) {
        QDomDocument doc;
        QFile file(svgFilePath);
        if (!file.open(QIODevice::ReadOnly)) {
            qWarning() << "Failed to open SVG file:" << file.fileName();
            return {};
        }
        if (!doc.setContent(&file)) {
            qWarning() << "Failed to parse SVG file:" << file.fileName();
            file.close();
            return {};
        }
        file.close();

        QDomNodeList elements = doc.elementsByTagName("*");
        for (const QString& ElementIds : elementIds) {
            QRectF elementBounds = renderer->boundsOnElement(ElementIds);
            if (elementBounds.contains(position)) {
                return ElementIds;
            }
        }
    }
    return {};
}

QStringList SVGHandleEvent::getElementIdsFromSvg(const QString &filePath) {
    QStringList elementIds;
    QString path = filePath.isEmpty() ? svgFilePath : filePath;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open SVG file:" << path;
        return elementIds;
    }

    QXmlStreamReader xml(&file);
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartElement) {
            if (xml.attributes().hasAttribute("id")) {
                elementIds.append(xml.attributes().value("id").toString());
            }
        }
    }

    if (xml.hasError()) {
        qWarning() << "Error parsing SVG file:" << xml.errorString();
    }

    file.close();
    return elementIds;
}

void SVGHandleEvent::saveAndReload(const QDomDocument& doc, const QString &path, const QString &elemID) {

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open SVG file for writing:" << path;
        return;
    }

    QTextStream stream(&file);
    stream << doc.toString();
    file.close();
    //qDebug() << "SVG file saved:" << path;

    reloadSVG(path,elemID);
}

void SVGHandleEvent::reloadSVG(const QString &reloadPath, const QString &elemID) {
    //qDebug() << "Reloading SVG file:" << reloadPath;


    this->renderer->load(reloadPath);
    this->update();
}

void SVGHandleEvent::vyhybkaMenu(const QPoint &pos, const QString &id) {
    QString m_value;
    QMenu contextMenu;
    contextMenu.addAction(id);
    contextMenu.addSeparator();

    QFile file(svgFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open SVG file:" << svgFilePath;
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qWarning() << "Failed to parse SVG file:" << svgFilePath;
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomNodeList elements = root.elementsByTagName("path");

    QString currentState;
    for (int i = 0; i < elements.count(); ++i) {
        QDomElement element = elements.at(i).toElement();
        if (element.isNull()) {
            continue;
        }
        QString Id = element.attribute("id");

        if (Id == "_basic" || Id == "_reverse") {
            QString visibility = element.attribute("visibility");
            if (visibility == "visible") {
                currentState = Id;
                break;
            }
        }
    }

    if (currentState == "_basic") {
        contextMenu.addAction("S-");
        qDebug() << "S-"<< id << " " << currentState << " file" << svgFilePath;
    } else if (currentState == "_reverse") {
        contextMenu.addAction("S+");
        qDebug() << "S+"<< id << " " << currentState << " file" << svgFilePath;
    }

    QAction* selectedAction = contextMenu.exec(pos);
    if (selectedAction) {
        m_value = selectedAction->text();
    }

    if (m_value == "S+") {
        threadToggleVyhybka(true, false,svgFilePath, id);
        //qDebug() << "S+";
    } else if (m_value == "S-") {
        //qDebug() << "S-";
        threadToggleVyhybka(false, true,svgFilePath,id);
    }
}

void SVGHandleEvent::toggleVisibility(bool straight, bool diverging, const QString &path, const QString &turnoutID) {
    std::lock_guard<std::mutex> lock(mtx_toggle_vyhybka);
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open SVG file:" << path;
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qWarning() << "Failed to parse SVG file:" << path;
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomNodeList elements = root.elementsByTagName("path");

    if (elements.isEmpty()) {
        qWarning() << "No path elements found in SVG file.";
        return;
    }

    auto extractNumber = [&](const QString &turnoutId) {
        QRegularExpression re("\\d+");
       // qDebug() << "extractNumber: " << turnoutId;
        QRegularExpressionMatch match = re.match(turnoutId);
        if (match.hasMatch()) {
            return match.captured(0);
        }
        return QString();
    };

    for (int i = 0; i < elements.count(); ++i) {
        QDomElement element = elements.at(i).toElement();
        if (element.isNull()) {
            continue;
        }
        QString id = element.attribute("id");

        if (id == "_basic" || id == "_reverse") {
            QString visibility = element.attribute("visibility");
            if (visibility == "visible") {
                element.setAttribute("visibility", "hidden");
            }
        }
    }

    auto setVisibility = [&](const QString &id, const QString &visibility) {
        for (int i = 0; i < elements.count(); ++i) {
            QDomElement element = elements.at(i).toElement();
            if (element.isNull()) {
                continue;
            }
            if (element.attribute("id") == id) {
                element.setAttribute("visibility", visibility);
            }
        }
    };

    if (straight) {
        setVisibility("_between", "visible");
        saveAndReload(doc,path,turnoutID);

        QString number = extractNumber(turnoutID);
        QString command = QString("<T %1 1>").arg(number);
       // qDebug() << "command: " << command;
        sendToArduino(command);
        std::this_thread::sleep_for(std::chrono::seconds(3));
        setVisibility("_between", "hidden");
        setVisibility("_basic", "visible");
        saveAndReload(doc,path,turnoutID);

    } else if (diverging) {
        setVisibility("_between", "visible");
        saveAndReload(doc,path,turnoutID);

        QString number = extractNumber(turnoutID);
        QString command = QString("<T %1 0>").arg(number);
        //qDebug() << "command: " << command;
        sendToArduino(command);
        std::this_thread::sleep_for(std::chrono::seconds(3));
        setVisibility("_between", "hidden");
        setVisibility("_reverse", "visible");
        saveAndReload(doc,path,turnoutID);
    }

    // qDebug() << "Exiting toggleVisibility method";
}



void SVGHandleEvent::updateTransform(const QString &transformStr) {
    QFile file(svgFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open SVG file:" << svgFilePath;
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qWarning() << "Failed to parse SVG file:" << svgFilePath;
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomElement gElement = root.firstChildElement("g");

    if (!gElement.isNull()) {
        gElement.setAttribute("transform", transformStr);
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open SVG file for writing:" << svgFilePath;
        return;
    }

    QTextStream stream(&file);
    stream << doc.toString();
    file.close();

    this->renderer->load(svgFilePath);
    this->update();
}

void SVGHandleEvent::vlakovaCestaRoute() {
    // Setting background color of that element to Lightgreen
    // Updating parameter in SVG file visibility with id back_color
    changeColorbackground(svgFilePath,elementId);

    // Read routes.xml to find the end point
    QFile routesFile("../layout/routes.xml");
    if (!routesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open routes.xml";
        return;
    }

    QDomDocument routesDoc;
    if (!routesDoc.setContent(&routesFile)) {
        qWarning() << "Failed to parse routes.xml";
        routesFile.close();
        return;
    }
    routesFile.close();

    QDomElement routesRoot = routesDoc.documentElement();
    QDomNodeList routes = routesRoot.elementsByTagName("route");

    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        QDomElement start = route.firstChildElement("start");
        if (start.attribute("point") == elementId) {
            QDomElement end = route.firstChildElement("end");
            QString endPointId = end.attribute("point");
            qDebug() << "End point:" << endPointId;

            // Update onDemand parameter to true
            QDomElement status = route.firstChildElement("status");
            QDomElement onDemand = status.firstChildElement("onDemand");
            onDemand.firstChild().setNodeValue("true");

            // Save the changes back to the routes.xml file
            if (!routesFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                qWarning() << "Failed to open routes.xml for writing";
                return;
            }

            QTextStream routesStream(&routesFile);
            routesStream << routesDoc.toString();
            routesFile.close();
        }
    }
}


void SVGHandleEvent::hlavneNavestidloMenu(const QPoint &pos, const QString &id) {

    QMenu contextMenu;
    contextMenu.addAction(id);
    contextMenu.addSeparator();

    // Load default values from hlavne_navestidlo.xml
    QFile file("../layout/menu_navestidla/hlavne_navestidlo.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open hlavne_navestidlo.xml";
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qWarning() << "Failed to parse hlavne_navestidlo.xml";
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomNodeList parameters = root.childNodes();

    for (int i = 0; i < parameters.count(); ++i) {
        QDomElement element = parameters.at(i).toElement();
        QString value = element.text();
        contextMenu.addAction(value);
    }

    QAction* selectedAction = contextMenu.exec(pos);
    if (selectedAction && selectedAction->text() == "VC") {
        vlakovaCestaRoute();
    }
}

void SVGHandleEvent::zriadovacieNavestidloMenu(const QPoint &pos, const QString &id){
    QMenu contextMenu;
    contextMenu.addAction(id);
    contextMenu.addSeparator();

    // Load default values from hlavne_navestidlo.xml
    QFile file("../layout/menu_navestidla/zriadovacie_navestidlo.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open hlavne_navestidlo.xml";
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qWarning() << "Failed to parse zriadovacie_navestidlo.xml";
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomNodeList parameters = root.childNodes();

    for (int i = 0; i < parameters.count(); ++i) {
        QDomElement element = parameters.at(i).toElement();
        QString value = element.text();
        contextMenu.addAction(value);
    }

    contextMenu.exec(pos);
}



void SVGHandleEvent::checkIDwithEndpoint(const QString &elementid) {
    QFile routesFile("../layout/routes.xml");
    if (!routesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open routes.xml";
        return;
    }

    QDomDocument routesDoc;
    if (!routesDoc.setContent(&routesFile)) {
        qWarning() << "Failed to parse routes.xml";
        routesFile.close();
        return;
    }
    routesFile.close();

    QDomElement routesRoot = routesDoc.documentElement();
    QDomNodeList routes = routesRoot.elementsByTagName("route");

    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        QDomElement end = route.firstChildElement("end");
        if (end.attribute("point") == elementid) {
            QDomElement status = route.firstChildElement("status");
            QDomElement onDemand = status.firstChildElement("onDemand");
            if (onDemand.text() == "true") {
                changeColorbackground(svgFilePath, elementid);
                qDebug() << "choosing this endpoint" << elementid;
                changingPositionOfTurnouts(elementid);

                // Change the locked parameter to true
                QDomElement locked = status.firstChildElement("locked");
                locked.firstChild().setNodeValue("true");

                // Save the changes back to the routes.xml file
                if (!routesFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    qWarning() << "Failed to open routes.xml for writing";
                    return;
                }

                QTextStream routesStream(&routesFile);
                routesStream << routesDoc.toString();
                routesFile.close();
                break;
            }
        }
    }
}


void SVGHandleEvent::changingPositionOfTurnouts(const QString &m_elementId) {
    qDebug() << "I get this endpoint" << m_elementId;
    QFile routesFile("../layout/routes.xml");
    if (!routesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open routes.xml";
        return;
    }

    QDomDocument routesDoc;
    if (!routesDoc.setContent(&routesFile)) {
        qWarning() << "Failed to parse routes.xml";
        routesFile.close();
        return;
    }
    routesFile.close();

    QDomElement routesRoot = routesDoc.documentElement();
    QDomNodeList routes = routesRoot.elementsByTagName("route");

    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        QDomElement end = route.firstChildElement("end");

        // Check if the endpoint matches the desired endpoint
        if (end.attribute("point") == m_elementId) {
            QDomNodeList elements = route.elementsByTagName("element");

            for (int j = 0; j < elements.count(); ++j) {
                QDomElement element = elements.at(j).toElement();
                QString id = element.attribute("id");
                QString desiredPosition = element.attribute("position");

                if (id.startsWith("T")) {
                    // Find the existing SVGHandleEvent item for the specific turnout
                    SVGHandleEvent *turnoutItem = nullptr;
                    for (QGraphicsItem *item : this->scene()->items()) {
                        SVGHandleEvent *svgItem = dynamic_cast<SVGHandleEvent *>(item);
                        if (svgItem && svgItem->elementId == id) {
                            turnoutItem = svgItem;
                            break;
                        }
                    }

                    if (!turnoutItem) {
                        qWarning() << "Turnout item not found for ID:" << id;
                        continue;
                    }

                    // Load the SVG file and parse it to get the current state of the turnout
                    QFile file(turnoutItem->svgFilePath);
                    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                        qWarning() << "Failed to open SVG file:" << turnoutItem->svgFilePath;
                        continue;
                    }

                    QDomDocument doc;
                    if (!doc.setContent(&file)) {
                        qWarning() << "Failed to parse SVG file:" << turnoutItem->svgFilePath;
                        file.close();
                        continue;
                    }
                    file.close();

                    QDomElement root = doc.documentElement();
                    QDomNodeList paths = root.elementsByTagName("path");

                    QString currentState;
                    for (int k = 0; k < paths.count(); ++k) {
                        QDomElement path = paths.at(k).toElement();
                        if (path.isNull()) {
                            continue;
                        }
                        QString pathId = path.attribute("id");

                        if (pathId == "_basic" || pathId == "_reverse") {
                            QString visibility = path.attribute("visibility");
                            if (visibility == "visible") {
                                currentState = pathId;
                                break;
                            }
                        }
                    }

                    // Determine the switch state and call threadToggleVyhybka with the appropriate parameters if needed
                    if ((currentState == "_basic" && desiredPosition == "S+") ||
                        (currentState == "_reverse" && desiredPosition == "S-")) {
                        qDebug() << "Turnout ID:" << id << "needs to be in the position:" << desiredPosition << "and is already in that position.";
                        // No action needed, already in the desired position
                        continue;
                    } else if (desiredPosition == "S-") {
                        turnoutItem->threadToggleVyhybka(false, true, turnoutItem->svgFilePath, id);
                    } else if (desiredPosition == "S+") {
                        turnoutItem->threadToggleVyhybka(true, false, turnoutItem->svgFilePath, id);
                    } else {
                        qWarning() << "Unknown desired position for ID:" << id;
                    }
                }
            }
        }
    }
}





