#include "ClickableSvgItem.h"
#include <QSvgRenderer>

ClickableSvgItem::ClickableSvgItem(QGraphicsItem* parent)
        : QGraphicsSvgItem(parent) {
}

void ClickableSvgItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsSvgItem::mousePressEvent(event);

    QString id = getElementIdAtPosition(event->pos());
    qDebug() << "Element ID retrieved:" << id;

    if (id == "turnout_1") {
        toggleVisibility("turnout_1","turnout_1_straight", "turnout_1_diverging");
    }
}

void ClickableSvgItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    qDebug() << "Mouse Move Event:" << event->pos();
    QGraphicsSvgItem::mouseMoveEvent(event);
}

void ClickableSvgItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    qDebug() << "Mouse Release Event:" << event->pos();
    QGraphicsSvgItem::mouseReleaseEvent(event);
}

QString ClickableSvgItem::getElementIdAtPosition(const QPointF& position) {
    QSvgRenderer* renderer = this->renderer();
    if (!renderer) {
        return QString();
    }

    QStringList elementIds = getElementIdsFromSvg("../layout/layout.svg"); // Replace with actual SVG file path

    for (const QString& elementId : elementIds) {
        QRectF elementBounds = renderer->boundsOnElement(elementId);
        if (elementBounds.contains(position)) {
            return elementId;
        }
    }

    return QString();
}

QStringList ClickableSvgItem::getElementIdsFromSvg(const QString& filePath) {
    QStringList elementIds;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open SVG file:" << filePath;
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

QDomDocument ClickableSvgItem::loadSvgDocument() {
    QFile file("../layout/layout.svg"); // Replace with actual SVG file path
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open SVG file";
        return QDomDocument();
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qWarning() << "Failed to parse SVG file";
        file.close();
        return QDomDocument();
    }

    file.close();
    return doc;
}

void ClickableSvgItem::toggleVisibility(const QString& groupId, const QString& elementId1, const QString& elementId2) {
    QDomDocument doc = loadSvgDocument();
    if (doc.isNull()) {
        return;
    }

    QDomElement groupElement;
    QDomNodeList elements = doc.elementsByTagName("g");
    for (int i = 0; i < elements.count(); ++i) {
        QDomElement element = elements.at(i).toElement();
        if (element.isNull()) {
            continue;
        }
        if (element.attribute("id") == groupId) {
            groupElement = element;
            break;
        }
    }

    if (groupElement.isNull()) {
        qWarning() << "Group element not found in SVG";
        return;
    }

    QDomElement element1;
    QDomElement element2;
    QDomNodeList groupChildren = groupElement.childNodes();
    for (int i = 0; i < groupChildren.count(); ++i) {
        QDomElement element = groupChildren.at(i).toElement();
        if (element.isNull()) {
            continue;
        }
        if (element.attribute("id") == elementId1) {
            element1 = element;
        } else if (element.attribute("id") == elementId2) {
            element2 = element;
        }
        if (!element1.isNull() && !element2.isNull()) {
            break;
        }
    }

    if (element1.isNull() || element2.isNull()) {
        qWarning() << "Element not found in SVG";
        return;
    }

    QString visibility1 = element1.attribute("visibility");
    QString visibility2 = element2.attribute("visibility");

    if (visibility1 == "visible") {
        element1.setAttribute("visibility", "hidden");
        element2.setAttribute("visibility", "visible");
    } else {
        element1.setAttribute("visibility", "visible");
        element2.setAttribute("visibility", "hidden");
    }

    // Save the modified SVG back to the file
    QFile file("../layout/layout.svg"); // Replace with actual SVG file path
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open SVG file for writing";
        return;
    }

    QTextStream out(&file);
    doc.save(out, 4);
    file.close();

    // Reload the SVG content
    this->setSharedRenderer(new QSvgRenderer(QString("../layout/layout.svg")));
    update();
}