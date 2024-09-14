#include "ClickableSvgItem.h"
#include <QDomDocument>
#include <QFile>
#include <QDebug>
#include <QGraphicsScene>
#include <QPainterPath>
#include <QSvgRenderer>

ClickableSvgItem::ClickableSvgItem(const QString &fileName, QGraphicsItem *parent)
        : QGraphicsSvgItem(fileName, parent), stateAVisible(true), fileName(fileName) {
    qDebug() << "ClickableSvgItem created with file:" << fileName;

    // Initial state is A
    QDomDocument doc;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly) && doc.setContent(&file)) {
        QDomElement root = doc.documentElement();
        QDomNodeList elements = root.elementsByTagName("path");
        for (int i = 0; i < elements.count(); ++i) {
            QDomElement element = elements.at(i).toElement();
            QString id = element.attribute("id");
            if (id.endsWith("_straight")) {
                element.setAttribute("visibility", "visible");
                qDebug() << "Setting initial visibility of" << id << "to visible";
            } else if (id.endsWith("_diverging")) {
                element.setAttribute("visibility", "hidden");
                qDebug() << "Setting initial visibility of" << id << "to hidden";
            }

            // Extract bounding box and store it with the ID
            QSvgRenderer renderer(fileName);
            QRectF boundingBox = renderer.boundsOnElement(id);
            if (!boundingBox.isNull()) {
                elementBoundingBoxes[id] = boundingBox;
            }
        }
        file.close();
    } else {
        qDebug() << "Failed to open or parse file:" << fileName;
    }
}

void ClickableSvgItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "Mouse pressed at:" << event->scenePos();

    // Get the mouse click position
    QPointF clickPos = event->scenePos();

    // Iterate over stored bounding boxes and check if the click position is within any element's bounding box
    for (const auto &id : elementBoundingBoxes.keys()) {
        QRectF boundingBox = elementBoundingBoxes[id];
        if (boundingBox.contains(clickPos)) {
            qDebug() << "Clicked on item with ID:" << id;

            // Toggle visibility based on the clicked element
            toggleTurnoutState(id);
            return;
        }
    }

    // If no element was found, log and return
    qDebug() << "No element found at the clicked position.";
}

void ClickableSvgItem::toggleTurnoutState(const QString &clickedId) {
    // Toggle visibility
    stateAVisible = !stateAVisible;
    QDomDocument doc;
    QFile file(this->fileName);
    if (file.open(QIODevice::ReadOnly) && doc.setContent(&file)) {
        QDomElement root = doc.documentElement();
        QDomNodeList elements = root.elementsByTagName("path");
        for (int i = 0; i < elements.count(); ++i) {
            QDomElement element = elements.at(i).toElement();
            if (element.attribute("id") == clickedId + "_straight") {
                element.setAttribute("visibility", stateAVisible ? "visible" : "hidden");
                qDebug() << "Setting visibility of" << clickedId + "_straight" << "to" << (stateAVisible ? "visible" : "hidden");
            } else if (element.attribute("id") == clickedId + "_diverging") {
                element.setAttribute("visibility", stateAVisible ? "hidden" : "visible");
                qDebug() << "Setting visibility of" << clickedId + "_diverging" << "to" << (stateAVisible ? "hidden" : "visible");
            }
        }
        file.close();
    } else {
        qDebug() << "Failed to open or parse file:" << this->fileName;
    }
    update();
}

