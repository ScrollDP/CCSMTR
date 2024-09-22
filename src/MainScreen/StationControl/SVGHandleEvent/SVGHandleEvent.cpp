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
            vlakovaCestaRouteVC();
        }

        // Open and parse routes.xml
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

        bool isVC = false;
        bool isPC = false;

        for (int i = 0; i < routes.count(); ++i) {
            QDomElement route = routes.at(i).toElement();
            QDomElement end = route.firstChildElement("end");
            if (end.attribute("point") == elementId) {
                QDomElement status = route.firstChildElement("status");
                QDomElement VC = status.firstChildElement("VC");
                QDomElement PC = status.firstChildElement("PC");

                if (VC.text() == "true") {
                    isVC = true;
                }
                if (PC.text() == "true") {
                    isPC = true;
                }
                break;
            }
        }

        if (isVC) {
            stavanieVCCesty(elementId);
        }
        if (isPC) {
            stavaniePCCesty(elementId);
        }
    }
    if(event->button() == Qt::MiddleButton) {
        if (QRegularExpression("^HN\\d+$").match(elementId).hasMatch()) {
            hlavneNavestidloMenu(event->screenPos(), elementId);
        }
        else if(QRegularExpression("^T\\d+(_\\d+)?$").match(elementId).hasMatch()) {
            vyhybkaMenu(event->screenPos(), elementId);
        }
        else if(QRegularExpression("^ZN\\d+$").match(elementId).hasMatch()) {
            zriadovacieNavestidloMenu(event->screenPos(), elementId);
        }
    }
    if(event->button() == Qt::RightButton) {
        if(QRegularExpression("^ZN\\d+?$").match(elementId).hasMatch()) {
            vlakovaCestaRoutePC();
        }
        else if(QRegularExpression("^HN\\d+?$").match(elementId).hasMatch()) {
            vlakovaCestaRoutePC();
        }


    }
}

void SVGHandleEvent::threadToggleVyhybka(bool straight, bool diverging, const QString &path, const QString &elementId) {
    if (vyhybkaThread.joinable()) {
        vyhybkaThread.join();
    }
    vyhybkaThread = std::thread(&SVGHandleEvent::toggleVisibility, this, straight, diverging, path, elementId);
}

void SVGHandleEvent::threadToggleVyhybkaGroupTurnout(bool straight, bool diverging, const QString &path, const QString &elementId) {
    if (vyhybkaThreadGroupTurnout.joinable()) {
        vyhybkaThreadGroupTurnout.join();
    }
    vyhybkaThreadGroupTurnout = std::thread(&SVGHandleEvent::toggleVyhybkaInGroup, this, straight, diverging, path, elementId);
}

void SVGHandleEvent::setScaleAndPosition(qreal scale, qreal x, qreal y) {
    this->setScale(scale);
    this->setPos(x * scale, y * scale);
}

void SVGHandleEvent::changeBackgroundColor(const QString &path, const QString &elemID) {
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

    // Open and parse routes.xml
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

    QString backColorId = "back_color";
    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        QDomElement start = route.firstChildElement("start");
        QDomElement end = route.firstChildElement("end");
        if (start.attribute("point") == elemID) {
            QDomElement status = route.firstChildElement("status");
            QDomElement VC = status.firstChildElement("VC");
            QDomElement PC = status.firstChildElement("PC");

            if (VC.text() == "true") {
                backColorId = "back_color_VC";
            } else if (PC.text() == "true") {
                backColorId = "back_color_PC";
            }
            break;
        }
        if(end.attribute("point") == elemID) {
            qDebug() << "End point:" << elemID;
            QDomElement status = route.firstChildElement("status");
            QDomElement VC = status.firstChildElement("VC");
            QDomElement PC = status.firstChildElement("PC");

            if (VC.text() == "true") {
                backColorId = "back_color_VC";
            } else if (PC.text() == "true") {
                backColorId = "back_color_PC";
            }
            break;
        }
    }

    for (int i = 0; i < elements.count(); ++i) {
        QDomElement element = elements.at(i).toElement();
        if (element.isNull()) {
            continue;
        }
        QString Id = element.attribute("id");

        // Debugging output
        qDebug() << "Checking element with Id:" << Id << "against backColorId:" << backColorId;

        if (Id == backColorId) {
            element.setAttribute("visibility", "visible");
            QDomElement rect = element.firstChildElement("rect");
            if (!rect.isNull()) {
                qDebug() << "Null color";
            }
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
    reloadSVG(path, elemID);
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
        QRegularExpressionMatch match = re.match(turnoutId);
        if (match.hasMatch()) {
            return match.captured(0);
        }
        return QString();
    };

    // Load and parse layout.xml
    QFile layoutFile("../layout/layout.xml");
    if (!layoutFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open layout.xml";
        return;
    }

    QDomDocument layoutDoc;
    if (!layoutDoc.setContent(&layoutFile)) {
        qWarning() << "Failed to parse layout.xml";
        layoutFile.close();
        return;
    }
    layoutFile.close();

    QDomElement layoutRoot = layoutDoc.documentElement();
    QDomNodeList turnoutElements = layoutRoot.elementsByTagName("turnout");
    bool pared = false;
    int paredGroup = -1;

    for (int i = 0; i < turnoutElements.count(); ++i) {
        QDomElement turnoutElement = turnoutElements.at(i).toElement();
        if (turnoutElement.attribute("id") == turnoutID && turnoutElement.hasAttribute("pared")) {
            pared = true;
            paredGroup = turnoutElement.attribute("pared").toInt();
            break;
        }
    }

    for (int i = 0; i < turnoutElements.count(); ++i) {
        QDomElement turnoutElement = turnoutElements.at(i).toElement();
        if (turnoutElement.attribute("id") == turnoutID && turnoutElement.hasAttribute("pared")) {
            pared = true;
            paredGroup = turnoutElement.attribute("pared").toInt();
            break;
        }
    }
    if (pared) {
        QDomNodeList paredTurnouts = layoutRoot.elementsByTagName("paredTurnout");
        for (int i = 0; i < paredTurnouts.count(); ++i) {
            QDomElement paredTurnout = paredTurnouts.at(i).toElement();
            if (paredTurnout.attribute("pared").toInt() == paredGroup) {
                QStringList turnoutIDs;
                QDomNamedNodeMap attributes = paredTurnout.attributes();
                for (int j = 0; j < attributes.count(); ++j) {
                    QDomAttr attr = attributes.item(j).toAttr();
                    if (attr.name().startsWith("turnout")) {
                        turnoutIDs << attr.value();
                    }
                }
                // Display also path of that turnouts
                qDebug() << "Pared Turnout IDs:" << turnoutIDs.join(", ");


                for (const QString &id : turnoutIDs) {
                    QString m_value;

                    // Retrieve the correct svgFilePath for each turnout ID
                    QString turnoutSvgFilePath = getTurnoutSvgPath(id);

                    QFile file(turnoutSvgFilePath);
                    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                        qWarning() << "Failed to open SVG file:" << turnoutSvgFilePath;
                        return;
                    }

                    QDomDocument doc;
                    if (!doc.setContent(&file)) {
                        qWarning() << "Failed to parse SVG file:" << turnoutSvgFilePath;
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
                        m_value = "S-";
                        qDebug() << "S-" << id << " " << currentState << " file" << turnoutSvgFilePath;
                    } else if (currentState == "_reverse") {
                        m_value = "S+";
                        qDebug() << "S+" << id << " " << currentState << " file" << turnoutSvgFilePath;
                    }

                    SVGHandleEvent *turnoutItem = nullptr;
                    for (QGraphicsItem *item : this->scene()->items()) {
                        SVGHandleEvent *svgItem = dynamic_cast<SVGHandleEvent *>(item);
                        if (svgItem && svgItem->elementId == id) {
                            turnoutItem = svgItem;
                            break;
                        }
                    }

                    if (m_value == "S+") {
                        turnoutItem->threadToggleVyhybkaGroupTurnout(true, false, turnoutSvgFilePath, id);
                    } else if (m_value == "S-") {
                        turnoutItem->threadToggleVyhybkaGroupTurnout(false, true, turnoutSvgFilePath, id);
                    }
                }
                return;
            }
        }
    } else {
        qDebug() << "pared parameter is false or not set" << turnoutID;
    }

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
        saveAndReload(doc, path, turnoutID);

        QString number = extractNumber(turnoutID);
        QString command = QString("<T %1 1>").arg(number);
        sendToArduino(command);
        qDebug() << "Command sent to Arduino:" << command.toStdString();
        std::this_thread::sleep_for(std::chrono::seconds(3));
        setVisibility("_between", "hidden");
        setVisibility("_basic", "visible");
        saveAndReload(doc, path, turnoutID);

    } else if (diverging) {
        setVisibility("_between", "visible");
        saveAndReload(doc, path, turnoutID);

        QString number = extractNumber(turnoutID);
        QString command = QString("<T %1 0>").arg(number);
        sendToArduino(command);
        qDebug() << "Command sent to Arduino:" << command.toStdString();
        std::this_thread::sleep_for(std::chrono::seconds(3));
        setVisibility("_between", "hidden");
        setVisibility("_reverse", "visible");
        saveAndReload(doc, path, turnoutID);
    }
}

QString SVGHandleEvent::getTurnoutSvgPath(const QString &turnoutId) {
    QDir tmpDir(".tmp");
    if (!tmpDir.exists()) {
        qWarning() << "Directory .tmp does not exist";
        return QString();
    }

    QFileInfoList fileList = tmpDir.entryInfoList(QDir::Files);
    for (const QFileInfo &fileInfo : fileList) {
        if (fileInfo.fileName().contains(turnoutId)) {
            return fileInfo.filePath();
        }
    }

    qWarning() << "File for turnout ID" << turnoutId << "not found in .tmp directory";
    return QString();
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

void SVGHandleEvent::vlakovaCestaRouteVC() {
    // Setting background color of that element to Lightgreen
    // Updating parameter in SVG file visibility with id back_color


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
            //qDebug() << "End point:" << endPointId;

            // Update parameters to true
            QDomElement status = route.firstChildElement("status");
            QDomElement onDemand = status.firstChildElement("onDemand");
            QDomElement VC = status.firstChildElement("VC");
            onDemand.firstChild().setNodeValue("true");
            VC.firstChild().setNodeValue("true");

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
    changeBackgroundColor(svgFilePath,elementId);
}


void SVGHandleEvent::hlavneNavestidloMenu(const QPoint &pos, const QString &id) {
    QMenu contextMenu;
    contextMenu.addAction(id);
    contextMenu.addSeparator();

    // Open and parse routes.xml
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

    bool isLocked = false;
    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        QDomElement start = route.firstChildElement("start");
        QDomElement status = route.firstChildElement("status");
        QDomElement locked = status.firstChildElement("locked");

        if (start.attribute("point") == id && locked.text() == "true") {
            isLocked = true;
            break;
        }
    }

    if (isLocked) {
        contextMenu.addAction("RC");
    } else {
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
            if (value != "RC") {
                contextMenu.addAction(value);
            }
        }
    }

    QAction* selectedAction = contextMenu.exec(pos);
    if (selectedAction && selectedAction->text() == "VC") {
        vlakovaCestaRouteVC();
    }
    if (selectedAction && selectedAction->text() == "PC") {
        vlakovaCestaRoutePC();
        qDebug() << "PC";
    }
    if (selectedAction && selectedAction->text() == "RC") {
        rusenieCesty(id);
        qDebug() << "RC";
    }
}

void SVGHandleEvent::zriadovacieNavestidloMenu(const QPoint &pos, const QString &id){
    QMenu contextMenu;
    contextMenu.addAction(id);
    contextMenu.addSeparator();

    // Open and parse routes.xml
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

    bool isLocked = false;
    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        QDomElement start = route.firstChildElement("start");
        QDomElement status = route.firstChildElement("status");
        QDomElement locked = status.firstChildElement("locked");

        if (start.attribute("point") == id && locked.text() == "true") {
            isLocked = true;
            break;
        }
    }

    if (isLocked) {
        contextMenu.addAction("RC");
    } else {
        // Load default values from hlavne_navestidlo.xml
        QFile file("../layout/menu_navestidla/zriadovacie_navestidlo.xml");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Failed to open zriadovacie_navestidlo.xml";
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
            if (value != "RC") {
                contextMenu.addAction(value);
            }
        }
    }

    QAction* selectedAction = contextMenu.exec(pos);
    if (selectedAction && selectedAction->text() == "PC") {
        vlakovaCestaRoutePC();
        qDebug() << "PC";
    }
    if (selectedAction && selectedAction->text() == "RC") {
        rusenieCesty(id);
        qDebug() << "RC";
    }
}



void SVGHandleEvent::stavanieVCCesty(const QString &m_id) {
   // qDebug() << "Checking endpoint" << elementId;
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

    QString routeName;
    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        QDomElement end = route.firstChildElement("end");
        QDomElement status = route.firstChildElement("status");
        QDomElement onDemand = status.firstChildElement("onDemand");
        QDomElement VC = status.firstChildElement("VC");

        // Check if the endpoint matches the desired endpoint and onDemand is true
        if (end.attribute("point") == m_id && onDemand.text() == "true" && VC.text() == "true") {
            routeName = route.attribute("name");
            break;
        }
    }

    if (routeName.isEmpty()) {
        qWarning() << "No route found for endpoint:" << m_id << "with onDemand set to true in VC";
        return;
    }

    qDebug() << "Route name for endpoint" << m_id << "is" << routeName;

    // Proceed with the existing logic using the routeName
    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        if (route.attribute("name") == routeName) {
            QDomElement end = route.firstChildElement("end");

            // Check if the endpoint matches the desired endpoint
            if (end.attribute("point") == m_id) {
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
                           // qDebug() << "Turnout ID:" << id << "needs to be in the position:" << desiredPosition << "and is already in that position.";
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

                // Change the locked parameter to true
                QDomElement status = route.firstChildElement("status");
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
    changeBackgroundColor(svgFilePath,m_id);
    qDebug() <<"VC changing color";
}

void SVGHandleEvent::vlakovaCestaRoutePC() {
    // Setting background color of that element to Lightgreen
    // Updating parameter in SVG file visibility with id back_color
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

            // Update parameters to true
            QDomElement status = route.firstChildElement("status");
            QDomElement onDemand = status.firstChildElement("onDemand");
            QDomElement PC = status.firstChildElement("PC");
            onDemand.firstChild().setNodeValue("true");
            PC.firstChild().setNodeValue("true");

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
    changeBackgroundColor(svgFilePath,elementId);
}

void SVGHandleEvent::rusenieCesty(const QString &id) {
    // Open and parse routes.xml
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

    QString routeName;
    QString startPointId;

    // Find the route with the given id and get its name and start point
    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        QDomElement start = route.firstChildElement("start");
        if (start.attribute("point") == id) {
            routeName = route.attribute("name");
            startPointId = start.attribute("point");
            break;
        }
    }

    if (routeName.isEmpty()) {
        qWarning() << "No route found with start point:" << id;
        return;
    }

    // Change the color of all parameters in the route to gray and set locked and onDemand to false
    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        if (route.attribute("name") == routeName) {
            QDomNodeList elements = route.elementsByTagName("element");

            for (int j = 0; j < elements.count(); ++j) {
                QDomElement element = elements.at(j).toElement();
                QString elementId = element.attribute("id");
                changeBackgroundColor(svgFilePath, elementId);
            }

            QDomElement status = route.firstChildElement("status");
            QDomElement locked = status.firstChildElement("locked");
            QDomElement onDemand = status.firstChildElement("onDemand");
            QDomElement VC = status.firstChildElement("VC");
            QDomElement PC = status.firstChildElement("PC");

            locked.firstChild().setNodeValue("false");
            onDemand.firstChild().setNodeValue("false");
            if(VC.text() == "true") {
                VC.firstChild().setNodeValue("false");
            }
            if(PC.text() == "true") {
                PC.firstChild().setNodeValue("false");
            }
        }
    }

    // Change onDemand to false for all routes that have the same start point
    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        QDomElement start = route.firstChildElement("start");
        if (start.attribute("point") == startPointId) {
            QDomElement status = route.firstChildElement("status");
            QDomElement onDemand = status.firstChildElement("onDemand");
            QDomElement VC = status.firstChildElement("VC");
            QDomElement PC = status.firstChildElement("PC");
            onDemand.firstChild().setNodeValue("false");

            if(PC.text() == "true") {
                PC.firstChild().setNodeValue("false");
            }
            if(PC.text() == "true") {
                PC.firstChild().setNodeValue("false");
            }
        }
    }

    // Save the changes back to the routes.xml file
    if (!routesFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open routes.xml for writing";
        return;
    }

    QTextStream routesStream(&routesFile);
    routesStream << routesDoc.toString();
    routesFile.close();
}

void SVGHandleEvent::stavaniePCCesty(const QString &m_id){
    // qDebug() << "Checking endpoint" << elementId;
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

    QString routeName;
    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        QDomElement end = route.firstChildElement("end");
        QDomElement status = route.firstChildElement("status");
        QDomElement onDemand = status.firstChildElement("onDemand");
        QDomElement PC = status.firstChildElement("PC");

        // Check if the endpoint matches the desired endpoint and onDemand is true
        if (end.attribute("point") == m_id && onDemand.text() == "true" && PC.text() == "true") {
            routeName = route.attribute("name");
            break;
        }
    }

    if (routeName.isEmpty()) {
        qWarning() << "No route found for endpoint:" << m_id << "with onDemand set to true in PC";
        return;
    }

    qDebug() << "Route name for endpoint" << m_id << "is" << routeName;

    // Proceed with the existing logic using the routeName
    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        if (route.attribute("name") == routeName) {
            QDomElement end = route.firstChildElement("end");

            // Check if the endpoint matches the desired endpoint
            if (end.attribute("point") == m_id) {
                QDomNodeList elements = route.elementsByTagName("element");

                for (int j = 0; j < elements.count(); ++j) {
                    QDomElement element = elements.at(j).toElement();
                    QString id = element.attribute("id");
                    QString desiredPosition = element.attribute("position");


                    changeBackgroundColor(svgFilePath,m_id);

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
                            // qDebug() << "Turnout ID:" << id << "needs to be in the position:" << desiredPosition << "and is already in that position.";
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

                // Change the locked parameter to true
                QDomElement status = route.firstChildElement("status");
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
    changeBackgroundColor(svgFilePath,m_id);
    qDebug()<<"PC change color";

}

void SVGHandleEvent::toggleVyhybkaInGroup(bool straight, bool diverging, const QString &path, const QString &turnoutID){
    std::lock_guard<std::mutex> lock(mtx_toggle_vyhybka_group_turnout);
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
        saveAndReload(doc, path, turnoutID);

        QString number = extractNumber(turnoutID);
        QString command = QString("<T %1 1>").arg(number);
        sendToArduino(command);
        qDebug() << "Command sent to Arduino:" << command.toStdString();
        std::this_thread::sleep_for(std::chrono::seconds(3));
        setVisibility("_between", "hidden");
        setVisibility("_basic", "visible");
        saveAndReload(doc, path, turnoutID);

    } else if (diverging) {
        setVisibility("_between", "visible");
        saveAndReload(doc, path, turnoutID);

        QString number = extractNumber(turnoutID);
        QString command = QString("<T %1 0>").arg(number);
        sendToArduino(command);
        qDebug() << "Command sent to Arduino:" << command.toStdString();
        std::this_thread::sleep_for(std::chrono::seconds(3));
        setVisibility("_between", "hidden");
        setVisibility("_reverse", "visible");
        saveAndReload(doc, path, turnoutID);
    }
}
