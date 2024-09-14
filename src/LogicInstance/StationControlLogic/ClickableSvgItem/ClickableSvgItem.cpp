#include "ClickableSvgItem.h"

ClickableSvgItem::ClickableSvgItem(QGraphicsItem* parent)
        : QGraphicsSvgItem(parent) {
}

void ClickableSvgItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsSvgItem::mousePressEvent(event);

    QString id = getElementIdAtPosition(event->pos());
    qDebug() << "Element ID retrieved:" << id;

    if (!id.isEmpty()) {
        qDebug() << "Clicked on item with ID:" << id;
    } else {
        qDebug() << "Clicked on item with ID: unknown";
    }

    // Log additional information
    qDebug() << "Position:" << event->pos();
    qDebug() << "Bounding Rect:" << this->boundingRect();
    qDebug() << "Transform:" << this->transform();
    qDebug() << "Opacity:" << this->opacity();
    qDebug() << "Z Value:" << this->zValue();
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