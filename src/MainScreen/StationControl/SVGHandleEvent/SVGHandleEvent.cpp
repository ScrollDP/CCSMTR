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

void SVGHandleEvent::threadToggleVyhybka(bool straight, bool diverging) {
    if (vyhybkaThread.joinable()) {
        vyhybkaThread.join();
    }
    vyhybkaThread = std::thread(&SVGHandleEvent::toggleVisibility, this, straight, diverging);
}

void SVGHandleEvent::setScaleAndPosition(qreal scale, qreal x, qreal y) {
    this->setScale(scale);
    this->setPos(x * scale, y * scale);
}



[[maybe_unused]] QString SVGHandleEvent::getElementIdAtPosition(const QPointF &position) {
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


void SVGHandleEvent::toggleVisibility(bool straight, bool diverging) {
    std::lock_guard<std::mutex> lock(mtx_toggle_vyhybka);
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

    if (elements.isEmpty()) {
        qWarning() << "No path elements found in SVG file.";
        return;
    }

    auto extractNumber = [&](const QString &elementId) {
        QRegularExpression re("\\d+");
        QRegularExpressionMatch match = re.match(elementId);
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

        if (id == "_straight" || id == "_diverging") {
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
        saveAndReload(doc);

        QString number = extractNumber(elementId);
        QString command = QString("<T %1 1>").arg(number);
        qDebug() << "command: " << command;
        sendToArduino(command);
        std::this_thread::sleep_for(std::chrono::seconds(3));
        setVisibility("_between", "hidden");
        setVisibility("_straight", "visible");
        saveAndReload(doc);

    } else if (diverging) {
        setVisibility("_between", "visible");
        saveAndReload(doc);

        QString number = extractNumber(elementId);
        QString command = QString("<T %1 0>").arg(number);
        qDebug() << "command: " << command;
        sendToArduino(command);
        std::this_thread::sleep_for(std::chrono::seconds(3));
        setVisibility("_between", "hidden");
        setVisibility("_diverging", "visible");
        saveAndReload(doc);
    }

   // qDebug() << "Exiting toggleVisibility method";
}

void SVGHandleEvent::saveAndReload(const QDomDocument& doc) {

    QFile file(svgFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open SVG file for writing:" << svgFilePath;
        return;
    }

    QTextStream stream(&file);
    stream << doc.toString();
    file.close();

    reloadSVG();
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

    reloadSVG();
}

void SVGHandleEvent::changeColor(bool m_rightclicked, bool m_middleclicked) {
    rightclicked = m_rightclicked;
    middleclicked = m_middleclicked;

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
    QDomNodeList elements = root.elementsByTagName("g");
    QString currentColor;


    if(rightclicked) {
        for (int i = 0; i < elements.count(); ++i) {
            QDomElement element = elements.at(i).toElement();
            if (element.hasAttribute("stroke")) {
                currentColor = element.attribute("stroke");
                if (currentColor == "gray") {
                    element.setAttribute("stroke", "#00FF00");
                    if (element.hasAttribute("id") && element.attribute("id") != "zriadovacie_navestidlo") {
                        element.setAttribute("fill", "#00FF00");
                    }
                } else if (currentColor == "#00FF00") {
                    element.setAttribute("stroke", "red");
                    if (element.hasAttribute("id") && element.attribute("id") != "zriadovacie_navestidlo") {
                        element.setAttribute("fill", "red");
                    }
                } else if (currentColor == "red") {
                    element.setAttribute("stroke", "gray");
                    if (element.hasAttribute("id") && element.attribute("id") != "zriadovacie_navestidlo") {
                        element.setAttribute("fill", "gray");
                    }
                }
            }
        }

    }
    else if(middleclicked) {
        for (int i = 0; i < elements.count(); ++i) {
            QDomElement element = elements.at(i).toElement();
            if (element.hasAttribute("stroke")) {
                currentColor = element.attribute("stroke");
                if (currentColor == "gray") {
                    element.setAttribute("stroke", "white");
                    if (element.hasAttribute("id") && element.attribute("id") != "zriadovacie_navestidlo") {
                        element.setAttribute("fill", "white");
                    }
                } else if (currentColor == "white") {
                    element.setAttribute("stroke", "gray");
                    if (element.hasAttribute("id") && element.attribute("id") != "zriadovacie_navestidlo") {
                        element.setAttribute("fill", "gray");
                    }
                }
            }
        }
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open SVG file for writing:" << svgFilePath;
        return;
    }

    QTextStream stream(&file);
    stream << doc.toString();
    file.close();

    reloadSVG();

}

void SVGHandleEvent::reloadSVG() {
    this->renderer->load(svgFilePath);
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

        if (Id == "_straight" || Id == "_diverging") {
            QString visibility = element.attribute("visibility");
            if (visibility == "visible") {
                currentState = Id;
                break;
            }
        }
    }

    if (currentState == "_straight") {
        contextMenu.addAction("S-");
    } else if (currentState == "_diverging") {
        contextMenu.addAction("S+");
    }

    QAction* selectedAction = contextMenu.exec(pos);
    if (selectedAction) {
        m_value = selectedAction->text();
    }

    if (m_value == "S+") {
        threadToggleVyhybka(true, false);
        //qDebug() << "S+";
    } else if (m_value == "S-") {
        //qDebug() << "S-";
        threadToggleVyhybka(false, true);
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
        // Setting background color of that element to Lightgreen
        // Updating parameter in SVG file visibility with id back_color
        changeColorbackground();

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
            hlavneNavestidloMenu(event->screenPos(), elementId);
        }
        else if(QRegularExpression("^T\\d+$").match(elementId).hasMatch()) {
            vyhybkaMenu(event->screenPos(), elementId);
        }
        checkIDwithEndpoint(elementId);
    }
    if(event->button() == Qt::RightButton) {
        if(QRegularExpression("^ZN\\d+$").match(elementId).hasMatch()) {
            zriadovacieNavestidloMenu(event->screenPos(), elementId);
        }
    }
    if(event->button() == Qt::MiddleButton) {
        changeColor(false, true);
    }
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
                changeColorbackground();

                break;
            }
        }
    }
}

void SVGHandleEvent::changeColorbackground() {
    QFile file(svgFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open SVG file:" << svgFilePath;
        return;
    }

    QDomDocument adoc;
    if (!adoc.setContent(&file)) {
        qWarning() << "Failed to parse SVG file:" << svgFilePath;
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
        qWarning() << "Failed to open SVG file for writing:" << svgFilePath;
        return;
    }

    QTextStream stream(&file);
    stream << adoc.toString();
    file.close();

    // Reload the SVG to apply changes
    reloadSVG();
}


