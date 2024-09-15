#include "SVGHandleEvent.h"
#include <QGraphicsScene>
#include <QDomDocument>
#include <QRegularExpression>
#include <QGraphicsSceneMouseEvent>

SVGHandleEvent::SVGHandleEvent(const QString &svgFilePath, const QString &elementId, QGraphicsItem* parent)
        : QGraphicsSvgItem(parent),
        svgFilePath(svgFilePath),
          elementId(elementId),
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

void SVGHandleEvent::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsSvgItem::mousePressEvent(event);
    qDebug() << "Element ID:" << elementId;
}

QString SVGHandleEvent::getElementIdAtPosition(const QPointF &position) {
    QStringList elementIds = getElementIdsFromSvg(QString());
    for (const QString &id : elementIds) {
        QDomDocument doc;
        QFile file(svgFilePath);
        if (!file.open(QIODevice::ReadOnly)) {
            qWarning() << "Failed to open SVG file:" << file.fileName();
            return QString();
        }
        if (!doc.setContent(&file)) {
            qWarning() << "Failed to parse SVG file:" << file.fileName();
            file.close();
            return QString();
        }
        file.close();

        QDomNodeList elements = doc.elementsByTagName("*");
        for (const QString& elementId : elementIds) {
            QRectF elementBounds = renderer->boundsOnElement(elementId);
            if (elementBounds.contains(position)) {
                return elementId;
            }
        }
    }
    return QString();
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
