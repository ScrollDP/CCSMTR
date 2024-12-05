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
#include <QDebug>
#include <QVector>


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
    if (vyhybkaThreadGroupTurnout.joinable()) {
        vyhybkaThreadGroupTurnout.join();
    }
    if (checkTurnoutsThread.joinable()) {
        checkTurnoutsThread.join();
    }
    if (colorBackgroundThread.joinable()) {
        colorBackgroundThread.join();
    }
    if (stavanieVCCestyThread.joinable()) {
        stavanieVCCestyThread.join();
    }
    if (stavaniePCCestyThread.joinable()) {
        stavaniePCCestyThread.join();
    }
    if (reloadSVGThread.joinable()) {
        reloadSVGThread.join();
    }
    if (updateTurnoutStatusInLayoutThread.joinable()) {
        updateTurnoutStatusInLayoutThread.join();
    }
    if (changeColorOfElementsThread.joinable()) {
        changeColorOfElementsThread.join();
    }
    if(angToggleVisibilityThread.joinable()) {
        angToggleVisibilityThread.join();
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
            vlakovaCestaRouteVC(elementId);
            return;
        }

        threadStavanieVCCesty(elementId); //musia byť takto aby sa vôbec zavolali
        threadStavaniePCCesty(elementId); //musia byť takto aby sa vôbec zavolali

    }
    if(event->button() == Qt::MiddleButton) {
        if (QRegularExpression("^HN\\d+$").match(elementId).hasMatch()) {
            hlavneNavestidloMenu(event->screenPos(), elementId);
            return;
        }
        else if(QRegularExpression("^T\\d+(_\\d+)?$").match(elementId).hasMatch()) {
            vyhybkaMenu(event->screenPos(), elementId);
            return;
        }
        else if(QRegularExpression("^AT\\d+(_\\d+)?$").match(elementId).hasMatch()) {
            vyhybkaMenu(event->screenPos(), elementId);
            return;
        }
        else if(QRegularExpression("^ZN\\d+$").match(elementId).hasMatch()) {
            zriadovacieNavestidloMenu(event->screenPos(), elementId);
            return;
        }
    }
    if(event->button() == Qt::RightButton) {
        if(QRegularExpression("^ZN\\d+?$").match(elementId).hasMatch() || QRegularExpression("^HN\\d+?$").match(elementId).hasMatch()) {
            vlakovaCestaRoutePC(elementId);
            return;
        }


    }

}

void SVGHandleEvent::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsSvgItem::mouseDoubleClickEvent(event);
    //left ctrl + left click
    if(event->button() == Qt::LeftButton) {
        rusenieCesty(elementId);
        return;
    }
}

void SVGHandleEvent::threadToggleVyhybka(bool straight, bool diverging, const QString &path, const QString &m_elementID) {
    if (vyhybkaThread.joinable()) {
        vyhybkaThread.join();
    }
    vyhybkaThread = std::thread(&SVGHandleEvent::toggleVisibility, this, straight, diverging, path, m_elementID);
}

void SVGHandleEvent::threadToggleVyhybkaGroupTurnout(bool straight, bool diverging, const QString &path, const QString &m_elementID) {
    if (vyhybkaThreadGroupTurnout.joinable()) {
        vyhybkaThreadGroupTurnout.join();
    }
    vyhybkaThreadGroupTurnout = std::thread(&SVGHandleEvent::toggleVyhybkaInGroup, this, straight, diverging, path, m_elementID);
}

bool SVGHandleEvent::threadCheckTurnouts(const QString &routeName, const QString &m_id) {
    if (checkTurnoutsThread.joinable()) {
        checkTurnoutsThread.join();
    }

    bool result = false;
    checkTurnoutsThread = std::thread([&]() {
        result = checkTurnouts(routeName, m_id);
    });
    checkTurnoutsThread.join();
    return result;
}

void SVGHandleEvent::threadChangeBackgroundColor(const QString &m_routeName, const QString &typeRoute,bool stateOfStavanie) {
    if (colorBackgroundThread.joinable()) {
        colorBackgroundThread.join();
    }
    colorBackgroundThread = std::thread(&SVGHandleEvent::changeBackgroundColor, this, m_routeName, typeRoute, stateOfStavanie);
}

void SVGHandleEvent::threadUpdateTurnoutStatus(const QString &turnoutID, const QString &newStatus) {
    if (updateTurnoutStatusInLayoutThread.joinable()) {
        updateTurnoutStatusInLayoutThread.join();
    }
    updateTurnoutStatusInLayoutThread = std::thread(&SVGHandleEvent::updateTurnoutStatus, this, turnoutID, newStatus);
}

void SVGHandleEvent::threadStavanieVCCesty(const QString &elementid) {
    if (stavanieVCCestyThread.joinable()) {
        stavanieVCCestyThread.join();
    }
    stavanieVCCestyThread = std::thread(&SVGHandleEvent::stavanieVCCesty, this, elementid);
}

void SVGHandleEvent::threadStavaniePCCesty(const QString &elementid) {
    if (stavaniePCCestyThread.joinable()) {
        stavaniePCCestyThread.join();
    }
    stavaniePCCestyThread = std::thread(&SVGHandleEvent::stavaniePCCesty, this, elementid);
}

void SVGHandleEvent::threadReloadSVG(const QString &reloadPath) {
    if (reloadSVGThread.joinable()) {
        reloadSVGThread.join();
    }
    reloadSVGThread = std::thread(&SVGHandleEvent::reloadSVG, this, reloadPath);
}

void SVGHandleEvent::threadChangeColorOfElements(const QString &m_routeName, const QString &color, bool stateOfStavanie) {
    if (colorBackgroundThread.joinable()) {
        colorBackgroundThread.join();
    }
    colorBackgroundThread = std::thread(&SVGHandleEvent::changeColorOfElements, this, m_routeName, color, stateOfStavanie);
}

void SVGHandleEvent::threadAngToggleVisibility(QString status, const QString &path, const QString &elementId) {
    if(angToggleVisibilityThread.joinable()) {
        angToggleVisibilityThread.join();
    }
    angToggleVisibilityThread = std::thread(&SVGHandleEvent::angToggleVisibility, this, status, path, elementId);
}


void SVGHandleEvent::setScaleAndPosition(qreal scale, qreal x, qreal y) {
    this->setScale(scale);
    this->setPos(x * scale, y * scale);
}

void SVGHandleEvent::changeBackgroundColor(const QString &m_routeName, const QString &typeRoute, bool stateOfStavanie) {
    std::lock_guard<std::mutex> lock(mtx_color_background);

    // Open and parse routes.xml
    QDomDocument routesDoc;
    QFile routesFile("../layout/routes.xml");
    if (!routesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open routes.xml";
        return;
    }

    QXmlStreamReader xmlReader(&routesFile);
    if (!routesDoc.setContent(&routesFile, &xmlReader)) {
        qWarning() << "Failed to parse routes.xml. Error at line" << xmlReader.lineNumber() << ", column" << xmlReader.columnNumber() << ":" << xmlReader.errorString();
        routesFile.close();
        return;
    }
    routesFile.close();

    QDomElement routesRoot = routesDoc.documentElement();
    QDomNodeList routes = routesRoot.elementsByTagName("route");

    QString endPoint,startPoint;
    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        if (route.attribute("name") == m_routeName) {
            QDomElement marks = route.firstChildElement("marks");
            QDomElement end = marks.firstChildElement("end");
            QDomElement start = marks.firstChildElement("start");
            endPoint = end.attribute("point");
            startPoint = start.attribute("point");
            break;
        }
    }

    if (endPoint.isEmpty()) {
        qWarning() << "End point not found for route name:" << m_routeName;
        return;
    }
    if (startPoint.isEmpty()) {
        qWarning() << "Start point not found for route name:" << m_routeName;
        return;
    }

    qDebug() << "CCEnd point:" << endPoint << "Start point:" << startPoint;

    // Load the SVG file of the endpoint
    QString endpointSvgPath = getElementSvgPath(endPoint);
    QString startpointSvgPath = getElementSvgPath(startPoint);
    if (endpointSvgPath.isEmpty()) {
        qWarning() << "SVG file not found for endpoint:" << endPoint;
        return;
    }
    if (startpointSvgPath.isEmpty()) {
        qWarning() << "SVG file not found for endpoint:" << startPoint;
        return;
    }

    QFile svgFile(endpointSvgPath);

    if (!svgFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open SVG file:" << endpointSvgPath;
        return;
    }
    QFile m_svgFile(startpointSvgPath);
    if(!m_svgFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open SVG file:" << startpointSvgPath;
        return;
    }

    QDomDocument svgDoc;

    if (!svgDoc.setContent(&svgFile)) {
        qWarning() << "Failed to parse SVG file:" << endpointSvgPath;
        svgFile.close();
        return;
    }
    svgFile.close();
    QDomDocument m_svgDoc;
    if (!m_svgDoc.setContent(&m_svgFile)) {
        qWarning() << "Failed to parse SVG file:" << startpointSvgPath;
        m_svgFile.close();
        return;
    }
    m_svgFile.close();

    QDomElement root = svgDoc.documentElement();
    QDomElement m_root = m_svgDoc.documentElement();
    QDomNodeList elements = root.elementsByTagName("g");
    QDomNodeList m_elements = m_root.elementsByTagName("g");

    QMap<QString, QString> routeToColorMap = {
            {"VC", "back_color_VC"},
            {"PC", "back_color_PC"},
            // Add more mappings here as needed
    };

    QString targetId = routeToColorMap.value(typeRoute, QString());
    if (!targetId.isEmpty()) {
        for (int i = 0; i < elements.count(); ++i) {
            QDomElement element = elements.at(i).toElement();
            if (element.attribute("id") == targetId) {

                if (stateOfStavanie) {
                    element.setAttribute("visibility", "hidden");

                    QString m_targetId = routeToColorMap.value(typeRoute, QString());
                    if (!m_targetId.isEmpty()) {
                        for (int a = 0; a < m_elements.count(); ++a) {
                            QDomElement m_element = m_elements.at(a).toElement();
                            if (m_element.attribute("id") == m_targetId) {
                                qDebug() << "Target ID Startpoint changeColor" << startPoint << "path of start point svg" << startpointSvgPath;
                                m_element.setAttribute("visibility", "hidden");

                                // Find the corresponding QGraphicsSvgItem in the scene

                                SVGHandleEvent *HNItem = nullptr;
                                for (QGraphicsItem *item : this->scene()->items()) {
                                    SVGHandleEvent *svgItem = dynamic_cast<SVGHandleEvent *>(item);
                                    if (svgItem && svgItem->elementId == startPoint) {
                                        HNItem = svgItem;
                                        break;
                                    }
                                }

                                // Save the changes back to the SVG file
                                if (!m_svgFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                                    qWarning() << "Failed to open SVG file for writing:" << startpointSvgPath;
                                }

                                QTextStream m_stream(&m_svgFile);
                                m_stream << m_svgDoc.toString();
                                m_svgFile.close();

                                // Reload the SVG to apply changes
                                HNItem->threadReloadSVG(startpointSvgPath);
                                qDebug() << "Startpoint SVG file saved:" << startpointSvgPath;
                            }
                        }
                    } else {
                        qWarning() << "Unknown typeRoute:" << typeRoute;
                    }


                } else {
                    element.setAttribute("visibility", "visible");
                }
            }
        }
    } else {
        qWarning() << "Unknown typeRoute:" << typeRoute;
    }

    // Save the changes back to the SVG file
    if (!svgFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open SVG file for writing:" << endpointSvgPath;
    }

    QTextStream stream(&svgFile);
    stream << svgDoc.toString();
    svgFile.close();

    // Reload the SVG to apply changes
    threadReloadSVG(endpointSvgPath);

}

void SVGHandleEvent::changeColorOfElements(const QString &m_routeName, const QString &color, bool stateOfStavanie) {
    std::lock_guard<std::mutex> lock(mtx_change_color_of_elements);

    // Open and parse routes.xml
    QDomDocument routesDoc;
    QFile routesFile("../layout/routes.xml");
    if (!routesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open routes.xml";
        return;
    }
    if (!routesDoc.setContent(&routesFile)) {
        qWarning() << "Failed to parse routes.xml";
        routesFile.close();
        return;
    }
    routesFile.close();

    QDomElement routesRoot = routesDoc.documentElement();
    QDomNodeList routes = routesRoot.elementsByTagName("route");

    QVector<QString> elementsArray;
    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        if (route.attribute("name") == m_routeName) {
            QDomNodeList elements = route.firstChildElement("elements").elementsByTagName("element");
            for (int j = 0; j < elements.count(); ++j) {
                QDomElement element = elements.at(j).toElement();
                elementsArray.append(element.attribute("id"));
            }
            break;
        }
    }

    QString targetColor = stateOfStavanie ? "gray" : color;

    for (const QString &elementId : elementsArray) {
        SVGHandleEvent *svgItem = nullptr;
        for (QGraphicsItem *item : this->scene()->items()) {
            SVGHandleEvent *tempItem = dynamic_cast<SVGHandleEvent *>(item);
            if (tempItem && tempItem->elementId == elementId) {
                svgItem = tempItem;
                break;
            }
        }

        if (svgItem) {
            QDomDocument svgDoc;
            QFile svgFile(svgItem->svgFilePath);
            if (!svgFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qWarning() << "Failed to open SVG file:" << svgItem->svgFilePath;
                continue;
            }
            if (!svgDoc.setContent(&svgFile)) {
                qWarning() << "Failed to parse SVG file:" << svgItem->svgFilePath;
                svgFile.close();
                continue;
            }
            svgFile.close();

            QDomElement root = svgDoc.documentElement();
            QDomNodeList groups = root.elementsByTagName("g");

            for (int i = 0; i < groups.count(); ++i) {
                QDomElement group = groups.at(i).toElement();
                if (elementId.startsWith("R") || elementId.startsWith("-R")) {
                    if (group.attribute("id") == "rail" || group.attribute("id") == "rail_sklon") {
                        group.setAttribute("stroke", targetColor);
                    }
                } else if (elementId.startsWith("T")) {
                    if (group.attribute("id") == "turnout") {
                        group.setAttribute("stroke", targetColor);
                    }
                } else if (elementId.startsWith("ZN")) {
                    if (group.attribute("id") == "zriadovacie_navestidlo") {
                        group.setAttribute("stroke", targetColor);
                    }
                } else if (elementId.startsWith("HN")) {
                    if (group.attribute("id") == "hlavne_navestidlo") {
                        group.setAttribute("stroke", targetColor);
                        group.setAttribute("fill", targetColor);
                    }
                } else if (elementId.startsWith("Z")) {
                    if (group.attribute("id") == "zarazadlo") {
                        group.setAttribute("stroke", targetColor);
                    }
                } else if (elementId.startsWith("CT1")){
                    if (group.attribute("id") == "cross_turnout") {
                        group.setAttribute("stroke", targetColor);
                    }
                }

            }

            if (!svgFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                qWarning() << "Failed to open SVG file for writing:" << svgItem->svgFilePath;
                continue;
            }
            QTextStream stream(&svgFile);
            stream << svgDoc.toString();
            svgFile.close();

            svgItem->threadReloadSVG(svgItem->svgFilePath);
        }
    }
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

    threadReloadSVG(path);
}

void SVGHandleEvent::reloadSVG(const QString &reloadPath) {
    std::lock_guard<std::mutex> lock(mtx_reload_svg);
    //qDebug() << "Reloading SVG file:" << reloadPath;


    this->renderer->load(reloadPath);
    this->update();
}

QString SVGHandleEvent::getSvgFilePathForTurnout(const QString &turnoutId) {
    SVGHandleEvent *turnoutItem = nullptr;
    for (QGraphicsItem *item : this->scene()->items()) {
        auto *svgItem = dynamic_cast<SVGHandleEvent *>(item);
        if (svgItem && svgItem->elementId == turnoutId) {
            turnoutItem = svgItem;
            break;
        }
    }
    return turnoutItem ? turnoutItem->svgFilePath : QString();
}

void SVGHandleEvent::vyhybkaMenu(const QPoint &pos, const QString &id) {
    //qDebug() << "VyhybkaMenu, id:" << id;

    QString m_value;
    QMenu contextMenu;
    contextMenu.addAction(id);
    contextMenu.addSeparator();

    //condition to find ang turnout
    // Open and parse layout.xml
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

    //display via qDebug the type of turnout
    QString type;
    for (int i = 0; i < turnoutElements.count(); ++i) {
        QDomElement turnoutElement = turnoutElements.at(i).toElement();
        if (turnoutElement.attribute("id") == id) {
            type = turnoutElement.attribute("type");
            break;
        }
    }
   // qDebug() << "Type of turnout:" << type;


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
        if(type == "ang_turnout") {
            if (Id == "S++" || Id == "S--" || Id == "S+-" || Id == "S-+") {
                QString visibility = element.attribute("visibility");
                if (visibility == "visible") {
                    currentState = Id;
                    break;
                }
            }
        }
        else if (type == "turnout") {
            if (Id == "_basic" || Id == "_reverse") {
                QString visibility = element.attribute("visibility");
                if (visibility == "visible") {
                    currentState = Id;
                    break;
                }
            }
        }
    }

    if(QRegularExpression("^T\\d+(_\\d+)?$").match(id).hasMatch()) {
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
    else if(QRegularExpression("^AT\\d+(_\\d+)?$").match(id).hasMatch()) {
        QStringList allStates = {"S++", "S--", "S+-", "S-+"};
        allStates.removeAll(currentState);

        //displaying allStates
        //qDebug() << "All states:" << allStates.join(", ");

        for (const QString &state : allStates) {
            contextMenu.addAction(state);
        }


        QAction* selectedAction = contextMenu.exec(pos);
        if (selectedAction) {
            m_value = selectedAction->text();
        }

        // if one of allStates is selected continue to another method
        if (allStates.contains(m_value)) {
            qDebug() << "Selected state:" << m_value;
            threadAngToggleVisibility(m_value, svgFilePath, id);
        }


    }

}

void SVGHandleEvent::angToggleVisibility(QString status, const QString &path, const QString &elementId) {
    std::lock_guard<std::mutex> lock(mtx_toggle_vyhybka);

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

    QDomElement layoutRoot = layoutDoc.documentElement();
    QDomNodeList turnoutElements = layoutRoot.elementsByTagName("turnout");

    // Load the configuration file for the turnout
    QString configFilePath = QString(".tmp/svgConfigFiles/%1.xml").arg(elementId);
    QFile configFile(configFilePath);
    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open turnout config file:" << configFilePath;
        return;
    }

    QDomDocument configDoc;
    if (!configDoc.setContent(&configFile)) {
        qWarning() << "Failed to parse turnout config file:" << configFilePath;
        configFile.close();
        return;
    }
    configFile.close();

    int id1_positionTurnout_basic, id1_positionTurnout_reverse, id2_positionTurnout_basic, id2_positionTurnout_reverse = -1;

    QDomElement rootTurnout = configDoc.documentElement();
    QDomElement id1Element_basic = rootTurnout.firstChildElement("id1").firstChildElement("_basic");
    QDomElement id1Element_reverse = rootTurnout.firstChildElement("id1").firstChildElement("_reverse");
    QDomElement id2Element_basic = rootTurnout.firstChildElement("id2").firstChildElement("_basic");
    QDomElement id2Element_reverse = rootTurnout.firstChildElement("id2").firstChildElement("_reverse");

    if (!id1Element_basic.isNull() || !id1Element_reverse.isNull() || !id2Element_basic.isNull() || !id2Element_reverse.isNull()) {
        id1_positionTurnout_basic = id1Element_basic.text().toInt();
        id1_positionTurnout_reverse = id1Element_reverse.text().toInt();
        id2_positionTurnout_basic = id2Element_basic.text().toInt();
        id2_positionTurnout_reverse = id2Element_reverse.text().toInt();
    }

    qDebug() << "id1_positionTurnout_basic:" << id1_positionTurnout_basic << "id1_positionTurnout_reverse:" << id1_positionTurnout_reverse << "id2_positionTurnout_basic:" << id2_positionTurnout_basic << "id2_positionTurnout_reverse:" << id2_positionTurnout_reverse;


    //all visibility to hidden of that elementID
    for (int i = 0; i < elements.count(); ++i) {
        QDomElement element = elements.at(i).toElement();
        if (element.isNull()) {
            continue;
        }
        QString id = element.attribute("id");

        if (id == "S++" || id == "S--" || id == "S+-" || id == "S-+") {
            QString visibility = element.attribute("visibility");
            if (visibility == "visible") {
                element.setAttribute("visibility", "hidden");
            }
        }
    }

    //extract from elementId only numbers
    auto extractNumber = [&](const QString &turnoutId) {
        QRegularExpression re("\\d+");
        QRegularExpressionMatch match = re.match(turnoutId);
        if (match.hasMatch()) {
            return match.captured(0);
        }
        return QString();
    };

    auto setVisibility = [&](const QString &id, const QString &visibility) {
        for (int i = 0; i < elements.count(); ++i) {
            QDomElement element = elements.at(i).toElement();
            if (element.isNull()) {
                continue;
            }
            if (element.attribute("id") == id) {
                qDebug() << "Setting visibility of element:" << id << "to" << visibility;
                element.setAttribute("visibility", visibility);
            }
        }
    };



    if(status == "S++") {
        setVisibility("_between", "visible");
        saveAndReload(doc, path, elementId);
        QString numberID = extractNumber(elementId);
        QString command = QString("<T %1 %2>").arg(numberID).arg(id1_positionTurnout_basic);
        sendToArduino(command);
        QString command2 = QString("<T %1 %2>").arg(numberID).arg(id2_positionTurnout_basic);
        sendToArduino(command2);
        qDebug() << "Command sent to Arduino:" << command.toStdString();
        qDebug() << "Command sent to Arduino:" << command2.toStdString();
        std::this_thread::sleep_for(std::chrono::seconds(3));
        setVisibility("_between", "hidden");
        setVisibility("S++", "visible");

        saveAndReload(doc, path, elementId);
        threadUpdateTurnoutStatus(elementId, "S++");
    }
    else if(status == "S--") {
        setVisibility("_between", "visible");
        saveAndReload(doc, path, elementId);
        QString numberID = extractNumber(elementId);
        QString command = QString("<T %1 %2>").arg(numberID).arg(id1_positionTurnout_reverse);
        sendToArduino(command);
        QString command2 = QString("<T %1 %2>").arg(numberID).arg(id2_positionTurnout_reverse);
        sendToArduino(command2);
        qDebug() << "Command sent to Arduino:" << command.toStdString();
        qDebug() << "Command sent to Arduino:" << command2.toStdString();
        std::this_thread::sleep_for(std::chrono::seconds(3));
        setVisibility("_between", "hidden");
        setVisibility("S--", "visible");

        saveAndReload(doc, path, elementId);
        threadUpdateTurnoutStatus(elementId, "S--");
    }
    else if(status == "S+-") {
        setVisibility("_between", "visible");
        saveAndReload(doc, path, elementId);
        QString numberID = extractNumber(elementId);
        QString command = QString("<T %1 %2>").arg(numberID).arg(id1_positionTurnout_basic);
        sendToArduino(command);
        QString command2 = QString("<T %1 %2>").arg(numberID).arg(id2_positionTurnout_reverse);
        sendToArduino(command2);
        qDebug() << "Command sent to Arduino:" << command.toStdString();
        qDebug() << "Command sent to Arduino:" << command2.toStdString();
        std::this_thread::sleep_for(std::chrono::seconds(3));
        setVisibility("_between", "hidden");
        setVisibility("S+-", "visible");

        saveAndReload(doc, path, elementId);
        threadUpdateTurnoutStatus(elementId, "S+-");
    }
    else if(status == "S-+") {
        setVisibility("_between", "visible");
        saveAndReload(doc, path, elementId);
        QString numberID = extractNumber(elementId);
        QString command = QString("<T %1 %2>").arg(numberID).arg(id1_positionTurnout_reverse);
        sendToArduino(command);
        QString command2 = QString("<T %1 %2>").arg(numberID).arg(id2_positionTurnout_basic);
        sendToArduino(command2);
        qDebug() << "Command sent to Arduino:" << command.toStdString();
        qDebug() << "Command sent to Arduino:" << command2.toStdString();
        std::this_thread::sleep_for(std::chrono::seconds(3));
        setVisibility("_between", "hidden");
        setVisibility("S-+", "visible");

        saveAndReload(doc, path, elementId);
        threadUpdateTurnoutStatus(elementId, "S-+");



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

    int positionTurnout_basic = -1;
    int positionTurnout_reverse = -1;

    QString configFilePath = QString(".tmp/svgConfigFiles/%1.xml").arg(turnoutID);
    QFile configFile(configFilePath);
    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open turnout config file:" << configFilePath;
        return;
    }

    QDomDocument configDoc;
    if (!configDoc.setContent(&configFile)) {
        qWarning() << "Failed to parse turnout config file:" << configFilePath;
        configFile.close();
        return;
    }
    configFile.close();

    QDomElement rootTurnout = configDoc.documentElement();
    QDomElement basicElement = rootTurnout.firstChildElement("_basic");
    QDomElement reverseElement = rootTurnout.firstChildElement("_reverse");

    if (!basicElement.isNull()) {
        positionTurnout_basic = basicElement.text().toInt();
    }
    if (!reverseElement.isNull()) {
        positionTurnout_reverse = reverseElement.text().toInt();
    }


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
                    QString turnoutSvgFilePath = getElementSvgPath(id);

                    QFile sfile(turnoutSvgFilePath);
                    if (!sfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                        qWarning() << "Failed to open SVG file:" << turnoutSvgFilePath;
                        return;
                    }

                    QDomDocument Adoc;
                    if (!Adoc.setContent(&sfile)) {
                        qWarning() << "Failed to parse SVG file:" << turnoutSvgFilePath;
                        sfile.close();
                        return;
                    }
                    sfile.close();

                    QDomElement lroot = Adoc.documentElement();
                    QDomNodeList velements = lroot.elementsByTagName("path");

                    QString currentState;
                    for (int a = 0; a < velements.count(); ++a) {
                        QDomElement element = velements.at(a).toElement();
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
                        threadUpdateTurnoutStatus(id, "S+");
                    } else if (m_value == "S-") {
                        turnoutItem->threadToggleVyhybkaGroupTurnout(false, true, turnoutSvgFilePath, id);
                        threadUpdateTurnoutStatus(id, "S-");
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

        QString numberID = extractNumber(turnoutID);
        QString command = QString("<T %1 %2>").arg(numberID).arg(positionTurnout_basic);
        qDebug() << "positionTurnout_basic" << positionTurnout_basic;
        sendToArduino(command);
        qDebug() << "Command sent to Arduino:" << command.toStdString();
        std::this_thread::sleep_for(std::chrono::seconds(3));
        setVisibility("_between", "hidden");
        setVisibility("_basic", "visible");
        saveAndReload(doc, path, turnoutID);

        threadUpdateTurnoutStatus(turnoutID, "S+");

    } else if (diverging) {
        setVisibility("_between", "visible");
        saveAndReload(doc, path, turnoutID);

        QString numberID = extractNumber(turnoutID);
        QString command = QString("<T %1 %2>").arg(numberID).arg(positionTurnout_reverse);
        qDebug() << "positionTurnout_reverse" << positionTurnout_reverse;
        sendToArduino(command);
        qDebug() << "Command sent to Arduino:" << command.toStdString();
        std::this_thread::sleep_for(std::chrono::seconds(3));
        setVisibility("_between", "hidden");
        setVisibility("_reverse", "visible");
        saveAndReload(doc, path, turnoutID);

        threadUpdateTurnoutStatus(turnoutID, "S-");
    }
}

QString SVGHandleEvent::getElementSvgPath(const QString &m_elementId) {
    QDir tmpDir(".tmp/svgFiles");
    if (!tmpDir.exists()) {
        qWarning() << "Directory .tmp/svgFiles does not exist";
        return {};
    }

    QFileInfoList fileList = tmpDir.entryInfoList(QDir::Files);
    QRegularExpression re(QString(".*_%1\\.svg$").arg(QRegularExpression::escape(m_elementId)));

    for (const QFileInfo &fileInfo : fileList) {
        if (re.match(fileInfo.fileName()).hasMatch()) {
            return fileInfo.filePath();
        }
    }

    qWarning() << "File for ID" << m_elementId << "not found in .tmp/svgFiles directory";
    return {};
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

void SVGHandleEvent::vlakovaCestaRouteVC(const QString &m_elementID) {


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

    // Check if any route with the same start point is locked
    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        QDomElement marks = route.firstChildElement("marks");
        QDomElement start = marks.firstChildElement("start");

        if (start.attribute("point") == m_elementID) {
            QDomElement status = route.firstChildElement("status");
            QDomElement locked = status.firstChildElement("locked");

            if (locked.text() == "true") {
                qWarning() << "Route with start point" << m_elementID << "is locked, cannot proceed with vlakovaCestaRouteVC";
                return;
            }
        }
    }
    // Get the SVG file path for the clicked element
    QString m_svgFilePath = getElementSvgPath(m_elementID);
    qDebug() << "SVG file path vlakovaCestaRouteVC:" << m_svgFilePath;
    if (m_svgFilePath.isEmpty()) {
        qWarning() << "SVG file not found for element:" << m_elementID;
        return;
    }

    // Open and parse the SVG file
    QFile svgFile(m_svgFilePath);
    if (!svgFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open SVG file:" << m_svgFilePath;
        return;
    }

    QDomDocument svgDoc;
    if (!svgDoc.setContent(&svgFile)) {
        qWarning() << "Failed to parse SVG file:" << m_svgFilePath;
        svgFile.close();
        return;
    }
    svgFile.close();

    // Find the group element and change its visibility
    QDomElement root = svgDoc.documentElement();
    QDomNodeList elements = root.elementsByTagName("g");

    for (int i = 0; i < elements.count(); ++i) {
        QDomElement element = elements.at(i).toElement();
        if (element.attribute("id") == "back_color_VC") {
            element.setAttribute("visibility", "visible");
            break;
        }
    }

    // Save the changes back to the SVG file
    if (!svgFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open SVG file for writing:" << m_svgFilePath;
        return;
    }

    QTextStream m_stream(&svgFile);
    m_stream << svgDoc.toString();
    svgFile.close();

    // Reload the SVG to apply changes
    threadReloadSVG(m_svgFilePath);

    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        QDomElement marks = route.firstChildElement("marks");
        QDomElement start = marks.firstChildElement("start");

        if (start.attribute("point") == m_elementID) {
            QDomElement status = route.firstChildElement("status");
            QDomElement VC = status.firstChildElement("VC");
            QDomElement inUse = status.firstChildElement("inUse");

            // Update VC status and inUse parameter
            VC.firstChild().setNodeValue("true");
            inUse.setAttribute("name", m_elementID);
        }
    }

    // Save the changes back to routes.xml
    if (!routesFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open routes.xml for writing";
        return;
    }

    QTextStream stream(&routesFile);
    stream << routesDoc.toString();
    routesFile.close();
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
        QDomElement marks = route.firstChildElement("marks");
        QDomElement start = marks.firstChildElement("start");
        QDomElement end = marks.firstChildElement("end");
        QDomElement status = route.firstChildElement("status");
        QDomElement locked = status.firstChildElement("locked");

        if ((start.attribute("point") == id || end.attribute("point") == id) && locked.text() == "true") {
            isLocked = true;
            break;
        }
    }

    if (isLocked) {
        contextMenu.addAction("RC");
    } else {
        // Open and parse hlavne-navestidlo.xml
        QFile navestidloFile("../layout/menu_navestidla/hlavne_navestidlo.xml");
        if (!navestidloFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Failed to open hlavne-navestidlo.xml";
            return;
        }

        QDomDocument navestidloDoc;
        if (!navestidloDoc.setContent(&navestidloFile)) {
            qWarning() << "Failed to parse hlavne-navestidlo.xml";
            navestidloFile.close();
            return;
        }
        navestidloFile.close();

        QDomElement navestidloRoot = navestidloDoc.documentElement();
        QDomNodeList parameterNodes = navestidloRoot.childNodes();
        QStringList parameters;

        for (int i = 0; i < parameterNodes.count(); ++i) {
            QDomElement paramElement = parameterNodes.at(i).toElement();
            if (!paramElement.isNull()) {
                parameters.append(paramElement.tagName());
            }
        }

        for (const QString &param : parameters) {
            QDomElement element = navestidloRoot.firstChildElement(param);
            if (!element.isNull() && element.text() != "RC") {
                contextMenu.addAction(element.text());
            }
        }
    }

    QAction* selectedAction = contextMenu.exec(QCursor::pos());
    if (selectedAction) {
        if (selectedAction->text() == "VC") {
            vlakovaCestaRouteVC(id);
            qDebug() << "VC";
        } else if (selectedAction->text() == "PC") {
            vlakovaCestaRoutePC(id);
            qDebug() << "PC";
        } else if (selectedAction->text() == "RC") {
            rusenieCesty(id);
            qDebug() << "RC";
        }
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
        QDomElement marks = route.firstChildElement("marks");
        QDomElement start = marks.firstChildElement("start");
        QDomElement end = marks.firstChildElement("end");
        QDomElement status = route.firstChildElement("status");
        QDomElement locked = status.firstChildElement("locked");

        if ((start.attribute("point") == id || end.attribute("point") == id) && locked.text() == "true") {
            isLocked = true;
            break;
        }
    }

    if (isLocked) {
        contextMenu.addAction("RC");
    } else {
        // Open and parse hlavne-navestidlo.xml
        QFile navestidloFile("../layout/menu_navestidla/zriadovacie_navestidlo.xml");
        if (!navestidloFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Failed to open hlavne-zriadovacie_navestidlo.xml";
            return;
        }

        QDomDocument navestidloDoc;
        if (!navestidloDoc.setContent(&navestidloFile)) {
            qWarning() << "Failed to parse zriadovacie_navestidlo-navestidlo.xml";
            navestidloFile.close();
            return;
        }
        navestidloFile.close();

        QDomElement navestidloRoot = navestidloDoc.documentElement();
        QDomNodeList parameterNodes = navestidloRoot.childNodes();
        QStringList parameters;

        for (int i = 0; i < parameterNodes.count(); ++i) {
            QDomElement paramElement = parameterNodes.at(i).toElement();
            if (!paramElement.isNull()) {
                parameters.append(paramElement.tagName());
            }
        }

        for (const QString &param : parameters) {
            QDomElement element = navestidloRoot.firstChildElement(param);
            if (!element.isNull() && element.text() != "RC") {
                contextMenu.addAction(element.text());
            }
        }
    }

    QAction* selectedAction = contextMenu.exec(QCursor::pos());
    if (selectedAction) {
        if (selectedAction->text() == "PC") {
            vlakovaCestaRoutePC(id);
            qDebug() << "PC";
        } else if (selectedAction->text() == "RC") {
            rusenieCesty(id);
            qDebug() << "RC";
        }
    }
}

bool SVGHandleEvent::checkRouteBeforeStavanie(const QString &elementid) {
    // Open and parse routes.xml
    QFile routesFile("../layout/routes.xml");
    if (!routesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open routes.xml";
        return false;
    }

    QDomDocument routesDoc;
    if (!routesDoc.setContent(&routesFile)) {
        qWarning() << "Failed to parse routes.xml";
        routesFile.close();
        return false;
    }
    routesFile.close();

    QDomElement routesRoot = routesDoc.documentElement();
    QDomNodeList routes = routesRoot.elementsByTagName("route");

    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        QDomElement marks = route.firstChildElement("marks");
        QDomElement end = marks.firstChildElement("end");
        QDomElement status = route.firstChildElement("status");
        QDomElement locked = status.firstChildElement("locked");
        if (end.attribute("point") == elementid) {
            if (locked.text() == "true") {
                return true;
            }
        }


    }

    return false;
}

void SVGHandleEvent::stavanieVCCesty(const QString &m_elementId) {
    std::lock_guard<std::mutex> lock(mtx_stavanie_vc_cesty);
    if (checkRouteBeforeStavanie(m_elementId)) {
        qWarning() << "Route is locked, cannot proceed with stavanieVCCesty";
        return;
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

   /* for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        QDomElement status = route.firstChildElement("status");
        QDomElement VC = status.firstChildElement("VC");
        QDomElement PC = status.firstChildElement("PC");

        if (VC.text() == "true" && PC.text() == "false") {
            //qDebug() << "VC is true and PC is false";
        } else if (VC.text() == "false" && PC.text() == "true") {
            qDebug() << "VC is false and PC is true (VC cesta)" << route.attribute("name");
            return;
        }
    }*/

    QString startPoint;
    QString endPoint = m_elementId;

    // Find the start point from the inUse parameter
    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        QDomElement marks = route.firstChildElement("marks");
        QDomElement end = marks.firstChildElement("end");
        QDomElement status = route.firstChildElement("status");
        QDomElement inUse = status.firstChildElement("inUse");

        if (end.attribute("point") == m_elementId && !inUse.attribute("name").isEmpty()) {
            startPoint = inUse.attribute("name");
            break;
        }
    }

    if (startPoint.isEmpty()) {
        qWarning() << "Start point not found for element ID:" << m_elementId;
        return;
    }


// Extract all elements from the route to be used
    QDomElement targetRoute;
    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        QDomElement marks = route.firstChildElement("marks");
        QDomElement start = marks.firstChildElement("start");
        QDomElement end = marks.firstChildElement("end");

        if (start.attribute("point") == startPoint && end.attribute("point") == endPoint) {
            qDebug() << "Route found for start point:" << startPoint << "and end point:" << endPoint;
            targetRoute = route;
            break;
        }
    }

    // Check if isPC is true for the identified target route
    QDomElement status = targetRoute.firstChildElement("status");
    QDomElement isPC = status.firstChildElement("isPC");
    if (isPC.text() == "yes") {
        qWarning() << "Route isPC is true, cannot proceed with stavanieVCCesty";
        //return;
    }


    if (targetRoute.isNull()) {
        qWarning() << "Target route not found for start point:" << startPoint << "and end point:" << endPoint;
        return;
    }

    QDomNodeList targetElements = targetRoute.firstChildElement("elements").elementsByTagName("element");

// Store elements in an array
    QVector<QDomElement> elementsArray;
    for (int i = 0; i < targetElements.count(); ++i) {
        QDomElement element = targetElements.at(i).toElement();
        elementsArray.append(element);
    }

// Check each route's status for locked elements
    for (int j = 0; j < routes.count(); ++j) {
        QDomElement route = routes.at(j).toElement();
        if (route == targetRoute) {
            continue; // Skip the target route
        }

        QDomElement status = route.firstChildElement("status");
        if (!status.isNull() && status.firstChildElement("locked").text() == "true") {
            qDebug() << "Checking locked route:" << route.attribute("name");

            QDomNodeList elements = route.firstChildElement("elements").elementsByTagName("element");
            for (int k = 0; k < elements.count(); ++k) {
                QDomElement element = elements.at(k).toElement();
                for (const QDomElement &targetElement : elementsArray) {
                    if (element.attribute("id") == targetElement.attribute("id")) {
                        qDebug() << "Match found in route:" << route.attribute("name");
                        /*qDebug() << "Original route elements:";
                        for (const QDomElement &origElement : elementsArray) {
                            qDebug() << "Element ID:" << origElement.attribute("id");
                        }
                        qDebug() << "Matching route elements:";
                        for (int l = 0; l < elements.count(); ++l) {
                            QDomElement matchElement = elements.at(l).toElement();
                            qDebug() << "Element ID:" << matchElement.attribute("id");
                        }*/
                        return;
                    }
                }
            }
        }
    }
    // Continue with the rest of the existing code
    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        QDomElement marks = route.firstChildElement("marks");
        QDomElement start = marks.firstChildElement("start");
        QDomElement end = marks.firstChildElement("end");

        if (start.attribute("point") == startPoint && end.attribute("point") == endPoint) {
            QDomElement status = route.firstChildElement("status");
            QDomElement VC = status.firstChildElement("VC");
            QDomElement locked = status.firstChildElement("locked");

            if (VC.text() == "true" && locked.text() == "false") {
                threadChangeBackgroundColor(targetRoute.attribute("name"), "VC",false);
                QDomNodeList elements = route.firstChildElement("elements").childNodes();
                for (int j = 0; j < elements.count(); ++j) {
                    QDomElement element = elements.at(j).toElement();
                    QString id = element.attribute("id");

                    if (id.startsWith("T")) {
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

                        QString desiredPosition = element.attribute("position");
                        if ((currentState == "_basic" && desiredPosition == "S+") ||
                            (currentState == "_reverse" && desiredPosition == "S-")) {
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

                for (int i = 0; i < routes.count(); ++i) {
                    QDomElement route = routes.at(i).toElement();
                    QDomElement marks = route.firstChildElement("marks");
                    QDomElement end = marks.firstChildElement("end");
                    QDomElement status = route.firstChildElement("status");
                    QDomElement inUse = status.firstChildElement("inUse");

                    if (end.attribute("point") == m_elementId && !inUse.attribute("name").isEmpty()) {
                        QString startPoint = inUse.attribute("name");

                        for (int j = 0; j < routes.count(); ++j) {
                            QDomElement routeToCheck = routes.at(j).toElement();
                            QDomElement marksToCheck = routeToCheck.firstChildElement("marks");
                            QDomElement startToCheck = marksToCheck.firstChildElement("start");
                            QDomElement endToCheck = marksToCheck.firstChildElement("end");

                            if (startToCheck.attribute("point") == startPoint && endToCheck.attribute("point") == m_elementId) {
                                QDomElement statusToCheck = routeToCheck.firstChildElement("status");
                                QDomElement lockedToCheck = statusToCheck.firstChildElement("locked");

                                if (lockedToCheck.text() == "true") {
                                    qDebug() << "Route" << routeToCheck.attribute("name") << "is locked";
                                } else if (threadCheckTurnouts(routeToCheck.attribute("name"), m_elementId)) {
                                    lockedToCheck.firstChild().setNodeValue("true");
                                    qDebug() << "Route" << routeToCheck.attribute("name") << "is now locked";

                                }

                            }
                        }
                    }
                }


                // Set inUse attribute to blank for all routes with the same start point
                for (int i = 0; i < routes.count(); ++i) {
                    QDomElement route = routes.at(i).toElement();
                    QDomElement marks = route.firstChildElement("marks");
                    QDomElement start = marks.firstChildElement("start");

                    if (start.attribute("point") == startPoint) {
                        QDomElement status = route.firstChildElement("status");
                        QDomElement inUse = status.firstChildElement("inUse");
                        inUse.setAttribute("name", "");
                    }
                }


                // Save the changes back to routes.xml
                if (!routesFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    qWarning() << "Failed to open routes.xml for writing";
                    return;
                }

                QTextStream stream(&routesFile);
                stream << routesDoc.toString();
                routesFile.close();

                std::this_thread::sleep_for(std::chrono::seconds(4));
                threadChangeBackgroundColor(targetRoute.attribute("name"), "VC", true);
                threadChangeColorOfElements(targetRoute.attribute("name"), "#00FF00", false);


            } else {
                qDebug() << "Route is locked";
                qDebug() << "VC.text():" << VC.text() << "locked.text():" << locked.text() << "m_elementId:" << m_elementId;
            }
        }
    }

}

void SVGHandleEvent::vlakovaCestaRoutePC(const QString &m_elementID) {
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

    // Check if any route with the same start point is locked
    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        QDomElement marks = route.firstChildElement("marks");
        QDomElement start = marks.firstChildElement("start");

        if (start.attribute("point") == m_elementID) {
            QDomElement status = route.firstChildElement("status");
            QDomElement locked = status.firstChildElement("locked");

            if (locked.text() == "true") {
                qWarning() << "Route with start point" << m_elementID << "is locked, cannot proceed with vlakovaCestaRoutePC";
                return;
            }
        }
    }
    // Get the SVG file path for the clicked element
    QString m_svgFilePath = getElementSvgPath(m_elementID);
    qDebug() << "SVG file path vlakovaCestaRoutePC:" << m_svgFilePath;
    if (m_svgFilePath.isEmpty()) {
        qWarning() << "SVG file not found for element:" << m_elementID;
        return;
    }

    // Open and parse the SVG file
    QFile svgFile(m_svgFilePath);
    if (!svgFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open SVG file:" << m_svgFilePath;
        return;
    }

    QDomDocument svgDoc;
    if (!svgDoc.setContent(&svgFile)) {
        qWarning() << "Failed to parse SVG file:" << m_svgFilePath;
        svgFile.close();
        return;
    }
    svgFile.close();

    // Find the group element and change its visibility
    QDomElement root = svgDoc.documentElement();
    QDomNodeList elements = root.elementsByTagName("g");

    for (int i = 0; i < elements.count(); ++i) {
        QDomElement element = elements.at(i).toElement();
        if (element.attribute("id") == "back_color_PC") {
            element.setAttribute("visibility", "visible");
            break;
        }
    }

    // Save the changes back to the SVG file
    if (!svgFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open SVG file for writing:" << m_svgFilePath;
        return;
    }

    QTextStream m_stream(&svgFile);
    m_stream << svgDoc.toString();
    svgFile.close();

    // Reload the SVG to apply changes
    threadReloadSVG(m_svgFilePath);

    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        QDomElement marks = route.firstChildElement("marks");
        QDomElement start = marks.firstChildElement("start");

        if (start.attribute("point") == m_elementID) {
            QDomElement status = route.firstChildElement("status");
            QDomElement PC = status.firstChildElement("PC");
            QDomElement inUse = status.firstChildElement("inUse");

            // Update VC status and inUse parameter
            PC.firstChild().setNodeValue("true");
            inUse.setAttribute("name", m_elementID);
        }
    }

    // Save the changes back to routes.xml
    if (!routesFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open routes.xml for writing";
        return;
    }

    QTextStream stream(&routesFile);
    stream << routesDoc.toString();
    routesFile.close();

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

    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        QDomElement marks = route.firstChildElement("marks");
        QDomElement start = marks.firstChildElement("start");

        if (start.attribute("point") == id) {
            QDomElement status = route.firstChildElement("status");
            QDomElement locked = status.firstChildElement("locked");
            QDomElement VC = status.firstChildElement("VC");
            QDomElement PC = status.firstChildElement("PC");
            QDomElement inUse = status.firstChildElement("inUse");

            // Set locked to false, VC to false, and inUse to blank
            if (locked.text() == "true") {
                locked.firstChild().setNodeValue("false");
            }
            if (VC.text() == "true") {
                VC.firstChild().setNodeValue("false");
            }
            if (PC.text() == "true") {
                PC.firstChild().setNodeValue("false");
            }
            //inUse.setAttribute("name", "");

            qDebug() << "Route" << route.attribute("name") << "is now unlocked";
            threadChangeColorOfElements(route.attribute("name"), "gray", true);
        }

    }

    // Save the changes back to routes.xml
    if (!routesFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open routes.xml for writing";
        return;
    }

    QTextStream stream(&routesFile);
    stream << routesDoc.toString();
    routesFile.close();
}

void SVGHandleEvent::stavaniePCCesty(const QString &m_elementId) {
    std::lock_guard<std::mutex> lock(mtx_stavanie_pc_cesty);
    if (checkRouteBeforeStavanie(m_elementId)) {
        qWarning() << "Route is locked, cannot proceed with stavanieVCCesty";
        return;
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


    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        QDomElement status = route.firstChildElement("status");
        QDomElement VC = status.firstChildElement("VC");
        QDomElement PC = status.firstChildElement("PC");

        if (VC.text() == "true" && PC.text() == "false") {
            qDebug() << "VC is true and PC is false (PC cesta)";
            return;
        } else if (VC.text() == "false" && PC.text() == "true") {
            //qDebug() << "VC is false and PC is true";
        }
    }

    QString startPoint;
    QString endPoint = m_elementId;

    // Find the start point from the inUse parameter
    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        QDomElement marks = route.firstChildElement("marks");
        QDomElement end = marks.firstChildElement("end");
        QDomElement status = route.firstChildElement("status");
        QDomElement inUse = status.firstChildElement("inUse");

        if (end.attribute("point") == m_elementId && !inUse.attribute("name").isEmpty()) {
            startPoint = inUse.attribute("name");
            break;
        }
    }

    if (startPoint.isEmpty()) {
        qWarning() << "Start point not found for element ID:" << m_elementId;
        return;
    }


// Extract all elements from the route to be used
    QDomElement targetRoute;
    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        QDomElement marks = route.firstChildElement("marks");
        QDomElement start = marks.firstChildElement("start");
        QDomElement end = marks.firstChildElement("end");

        if (start.attribute("point") == startPoint && end.attribute("point") == endPoint) {
            qDebug() << "Route found for start point:" << startPoint << "and end point:" << endPoint;
            targetRoute = route;
            break;
        }
    }

    if (targetRoute.isNull()) {
        qWarning() << "Target route not found for start point:" << startPoint << "and end point:" << endPoint;
        return;
    }

    QDomNodeList targetElements = targetRoute.firstChildElement("elements").elementsByTagName("element");

// Store elements in an array
    QVector<QDomElement> elementsArray;
    for (int i = 0; i < targetElements.count(); ++i) {
        QDomElement element = targetElements.at(i).toElement();
        elementsArray.append(element);
    }

// Check each route's status for locked elements
    for (int j = 0; j < routes.count(); ++j) {
        QDomElement route = routes.at(j).toElement();
        if (route == targetRoute) {
            continue; // Skip the target route
        }

        QDomElement status = route.firstChildElement("status");
        if (!status.isNull() && status.firstChildElement("locked").text() == "true") {
            qDebug() << "Checking locked route:" << route.attribute("name");

            QDomNodeList elements = route.firstChildElement("elements").elementsByTagName("element");
            for (int k = 0; k < elements.count(); ++k) {
                QDomElement element = elements.at(k).toElement();
                for (const QDomElement &targetElement : elementsArray) {
                    if (element.attribute("id") == targetElement.attribute("id")) {
                        qDebug() << "Match found in route:" << route.attribute("name");
                        /*qDebug() << "Original route elements:";
                        for (const QDomElement &origElement : elementsArray) {
                            qDebug() << "Element ID:" << origElement.attribute("id");
                        }
                        qDebug() << "Matching route elements:";
                        for (int l = 0; l < elements.count(); ++l) {
                            QDomElement matchElement = elements.at(l).toElement();
                            qDebug() << "Element ID:" << matchElement.attribute("id");
                        }*/
                        return;
                    }
                }
            }
        }
    }
    // Continue with the rest of the existing code
    for (int i = 0; i < routes.count(); ++i) {
        QDomElement route = routes.at(i).toElement();
        QDomElement marks = route.firstChildElement("marks");
        QDomElement start = marks.firstChildElement("start");
        QDomElement end = marks.firstChildElement("end");

        if (start.attribute("point") == startPoint && end.attribute("point") == endPoint) {
            QDomElement status = route.firstChildElement("status");
            QDomElement PC = status.firstChildElement("PC");
            QDomElement locked = status.firstChildElement("locked");

            if (PC.text() == "true" && locked.text() == "false") {
                threadChangeBackgroundColor(targetRoute.attribute("name"), "PC",false);
                QDomNodeList elements = route.firstChildElement("elements").childNodes();
                for (int j = 0; j < elements.count(); ++j) {
                    QDomElement element = elements.at(j).toElement();
                    QString id = element.attribute("id");

                    if (id.startsWith("T")) {
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

                        QString desiredPosition = element.attribute("position");
                        if ((currentState == "_basic" && desiredPosition == "S+") ||
                            (currentState == "_reverse" && desiredPosition == "S-")) {
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

                for (int i = 0; i < routes.count(); ++i) {
                    QDomElement route = routes.at(i).toElement();
                    QDomElement marks = route.firstChildElement("marks");
                    QDomElement end = marks.firstChildElement("end");
                    QDomElement status = route.firstChildElement("status");
                    QDomElement inUse = status.firstChildElement("inUse");

                    if (end.attribute("point") == m_elementId && !inUse.attribute("name").isEmpty()) {
                        QString startPoint = inUse.attribute("name");

                        for (int j = 0; j < routes.count(); ++j) {
                            QDomElement routeToCheck = routes.at(j).toElement();
                            QDomElement marksToCheck = routeToCheck.firstChildElement("marks");
                            QDomElement startToCheck = marksToCheck.firstChildElement("start");
                            QDomElement endToCheck = marksToCheck.firstChildElement("end");

                            if (startToCheck.attribute("point") == startPoint && endToCheck.attribute("point") == m_elementId) {
                                QDomElement statusToCheck = routeToCheck.firstChildElement("status");
                                QDomElement lockedToCheck = statusToCheck.firstChildElement("locked");

                                if (lockedToCheck.text() == "true") {
                                    qDebug() << "Route" << routeToCheck.attribute("name") << "is locked";
                                } else if (threadCheckTurnouts(routeToCheck.attribute("name"), m_elementId)) {
                                    lockedToCheck.firstChild().setNodeValue("true");
                                    qDebug() << "Route" << routeToCheck.attribute("name") << "is now locked";
                                }
                            }
                        }
                    }
                }


                // Set inUse attribute to blank for all routes with the same start point
                for (int i = 0; i < routes.count(); ++i) {
                    QDomElement route = routes.at(i).toElement();
                    QDomElement marks = route.firstChildElement("marks");
                    QDomElement start = marks.firstChildElement("start");

                    if (start.attribute("point") == startPoint) {
                        QDomElement status = route.firstChildElement("status");
                        QDomElement inUse = status.firstChildElement("inUse");
                        inUse.setAttribute("name", "");
                    }
                }



                // Save the changes back to routes.xml
                if (!routesFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    qWarning() << "Failed to open routes.xml for writing";
                    return;
                }

                QTextStream stream(&routesFile);
                stream << routesDoc.toString();
                routesFile.close();

                std::this_thread::sleep_for(std::chrono::seconds(4));
                threadChangeBackgroundColor(targetRoute.attribute("name"), "PC", true);
                threadChangeColorOfElements(targetRoute.attribute("name"), "white", false);
            } else {
                qDebug() << "Route is locked";
                qDebug() << "PC.text():" << PC.text() << "locked.text():" << locked.text() << "m_elementId:" << m_elementId;
            }
        }
    }

}

bool SVGHandleEvent::checkTurnouts(const QString &routeName, const QString &m_id) {
    std::lock_guard<std::mutex> lock(mtx_check_turnouts);
    bool allTurnoutsInPosition = false;

    while (!allTurnoutsInPosition) {
        allTurnoutsInPosition = true;

        // Open and parse routes.xml
        QFile routesFile("../layout/routes.xml");
        if (!routesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Failed to open routes.xml";
            return false;
        }

        QDomDocument routesDoc;
        if (!routesDoc.setContent(&routesFile)) {
            qWarning() << "Failed to parse routes.xml";
            routesFile.close();
            return false;
        }
        routesFile.close();

        QDomElement routesRoot = routesDoc.documentElement();
        QDomNodeList routes = routesRoot.elementsByTagName("route");

        for (int i = 0; i < routes.count(); ++i) {
            QDomElement route = routes.at(i).toElement();
            if (route.attribute("name") == routeName) {
                QDomNodeList elements = route.firstChildElement("elements").childNodes();
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
                            allTurnoutsInPosition = false;
                            break;
                        }

                        // Load the SVG file and parse it to get the current state of the turnout
                        QFile file(turnoutItem->svgFilePath);
                        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                            qWarning() << "Failed to open SVG file:" << turnoutItem->svgFilePath;
                            allTurnoutsInPosition = false;
                            break;
                        }

                        QDomDocument doc;
                        if (!doc.setContent(&file)) {
                            qWarning() << "Failed to parse SVG file:" << turnoutItem->svgFilePath;
                            file.close();
                            allTurnoutsInPosition = false;
                            break;
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

                        // Determine the switch state
                        if ((currentState == "_basic" && desiredPosition != "S+") ||
                            (currentState == "_reverse" && desiredPosition != "S-")) {
                            allTurnoutsInPosition = false;
                            break;
                        }
                    }
                }
            }
        }

        if (!allTurnoutsInPosition) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        }
    }

    return allTurnoutsInPosition;
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


    int positionTurnout_basic = -1;
    int positionTurnout_reverse = -1;

    QString configFilePath = QString(".tmp/svgConfigFiles/%1.xml").arg(turnoutID);
    QFile configFile(configFilePath);
    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open turnout config file:" << configFilePath;
        return;
    }

    QDomDocument configDoc;
    if (!configDoc.setContent(&configFile)) {
        qWarning() << "Failed to parse turnout config file:" << configFilePath;
        configFile.close();
        return;
    }
    configFile.close();

    QDomElement rootTurnout = configDoc.documentElement();
    QDomElement basicElement = rootTurnout.firstChildElement("_basic");
    QDomElement reverseElement = rootTurnout.firstChildElement("_reverse");

    if (!basicElement.isNull()) {
        positionTurnout_basic = basicElement.text().toInt();
    }
    if (!reverseElement.isNull()) {
        positionTurnout_reverse = reverseElement.text().toInt();
    }


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
        QString command = QString("<T %1 %2>").arg(number).arg(positionTurnout_basic);
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
        QString command = QString("<T %1 %2>").arg(number).arg(positionTurnout_reverse);
        sendToArduino(command);
        qDebug() << "Command sent to Arduino:" << command.toStdString();
        std::this_thread::sleep_for(std::chrono::seconds(3));
        setVisibility("_between", "hidden");
        setVisibility("_reverse", "visible");
        saveAndReload(doc, path, turnoutID);
    }
}

void SVGHandleEvent::updateTurnoutStatus(const QString &turnoutID, const QString &newStatus) {
    static std::timed_mutex mtx_update_turnout_status;
    if (!mtx_update_turnout_status.try_lock_for(std::chrono::milliseconds(200))) {
        return;
    }
    std::lock_guard<std::timed_mutex> lock(mtx_update_turnout_status, std::adopt_lock);

    QString turnoutConfigPath = QString(".tmp/svgConfigFiles/%1.xml").arg(turnoutID);
    QFile turnoutConfigFile(turnoutConfigPath);
    if (!turnoutConfigFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open turnout config file:" << turnoutConfigPath;
        return;
    }

    QDomDocument turnoutConfigDoc;
    if (!turnoutConfigDoc.setContent(&turnoutConfigFile)) {
        qWarning() << "Failed to parse turnout config file:" << turnoutConfigPath;
        turnoutConfigFile.close();
        return;
    }
    turnoutConfigFile.close();

    QDomElement turnoutConfigRoot = turnoutConfigDoc.documentElement();
    QDomElement statusElement = turnoutConfigRoot.firstChildElement("status");
    statusElement.firstChild().setNodeValue(newStatus);

    if (!turnoutConfigFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open turnout config file for writing:" << turnoutConfigPath;
        return;
    }

    QTextStream stream(&turnoutConfigFile);
    stream << turnoutConfigDoc.toString();
    turnoutConfigFile.close();
}
