#include "SVGHandleEvent.h"
#include <QGraphicsScene>
#include <QDomDocument>
#include <QRegularExpression>
#include <QGraphicsSceneMouseEvent>
#include <utility>
#include <QMenu>
#include <QTimer>
#include <iostream>
#include <QEventLoop>

SVGHandleEvent::SVGHandleEvent(const QString &svgFilePath, QString elementId, int row, int col, bool flipped, int rotate, QGraphicsItem* parent)
        : QGraphicsSvgItem(parent),
        svgFilePath(svgFilePath),
        elementId(std::move(elementId)),
        row(row),
        col(col),
        flipped(flipped),
        rotate(rotate),
        renderer(new QSvgRenderer(svgFilePath)) {
    if (!renderer->isValid()) {
        qWarning() << "Failed to load SVG file:" << svgFilePath;
        delete renderer;
        renderer = nullptr;
        return;
    }
    this->setSharedRenderer(renderer);

}

void SVGHandleEvent::setScaleAndPosition(qreal scale, qreal x, qreal y) {
    this->setScale(scale);
    this->setPos(x * scale, y * scale);
}

[[maybe_unused]] void SVGHandleEvent::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsSvgItem::mousePressEvent(event);
    if(event->button() == Qt::LeftButton) {

        qDebug() << "Element ID:" << elementId << "|Row:" << row <<"|Col:" << col <<
        "|Flipped:" << flipped << "|Rotate:" << rotate << "|File:" << svgFilePath;


        if (QRegularExpression("^HN\\d+$").match(elementId).hasMatch()) {
            hlavneNavestidloMenu(event->screenPos(), elementId);
            return;
        }
        else if(QRegularExpression("^T\\d+$").match(elementId).hasMatch()) {
            //toggleVisibility(true,false);
            vyhybkaMenu(event->screenPos(), elementId);
            return;
        }
        return;

    }
    if(event->button() == Qt::RightButton) {
        if(QRegularExpression("^ZN\\d+$").match(elementId).hasMatch()) {
            zriadovacieNavestidloMenu(event->screenPos(), elementId);
            return;
        }
        return;
    }
    if(event->button() == Qt::MiddleButton) {
        changeColor(false, true);
        return;
    }
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

    QString currentState;
    for (int i = 0; i < elements.count(); ++i) {
        QDomElement element = elements.at(i).toElement();
        if (element.isNull()) {
            continue;
        }
        QString id = element.attribute("id");

        if (id == "_straight" || id == "_diverging") {
            QString visibility = element.attribute("visibility");
            if (visibility == "visible") {
                currentState = id;
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
        qDebug() << "Switching to straight";
        setVisibility("_between", "visible");
        saveAndReload(doc);
        QEventLoop loop;
        QTimer::singleShot(3000, &loop, &QEventLoop::quit);
        loop.exec();
        setVisibility("_between", "hidden");
        setVisibility("_straight", "visible");
        saveAndReload(doc);
    } else if (diverging) {
        qDebug() << "Switching to diverging";
        setVisibility("_between", "visible");
        saveAndReload(doc);
        QEventLoop loop;
        QTimer::singleShot(3000, &loop, &QEventLoop::quit);
        loop.exec();
        setVisibility("_between", "hidden");
        setVisibility("_diverging", "visible");
        saveAndReload(doc);
    }

    saveAndReload(doc);
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

    QFile file("../layout/menu_vyhybky/vyhybky.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open vyhybky.xml";
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qWarning() << "Failed to parse vyhybky.xml";
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomNodeList parameters = root.childNodes();

    if (parameters.isEmpty()) {
        qWarning() << "No parameters found in vyhybky.xml.";
        return;
    }

    for (int i = 0; i < parameters.count(); ++i) {
        QDomElement element = parameters.at(i).toElement();
        if (element.isNull()) {
            continue;
        }
        QString value = element.text();
        contextMenu.addAction(value);

    }
    QAction* selectedAction = contextMenu.exec(pos);
    if (selectedAction) {
        m_value = selectedAction->text();
    }

    if (m_value == "S+") {
        toggleVisibility(true, false);
        qDebug() << "S+";
    } else if (m_value == "S-") {
        qDebug() << "S-";
        toggleVisibility(false, true);
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

    contextMenu.exec(pos);
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