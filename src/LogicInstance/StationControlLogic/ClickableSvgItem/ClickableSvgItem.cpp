#include "ClickableSvgItem.h"

ClickableSvgItem::ClickableSvgItem(QGraphicsItem* parent)
        : QGraphicsSvgItem(parent) {
}

void ClickableSvgItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsSvgItem::mousePressEvent(event);

    QString id = this->elementId();
    if (!id.isEmpty()) {
        qDebug() << "Clicked on item with ID:" << id;
    } else {
        qDebug() << "Clicked on item with ID: unknown";
    }
}