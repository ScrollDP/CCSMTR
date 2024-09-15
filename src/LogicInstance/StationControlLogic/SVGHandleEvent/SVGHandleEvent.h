#ifndef CLICKABLESVGITEM_H
#define CLICKABLESVGITEM_H

#include <QGraphicsSvgItem>
#include <QGraphicsSceneMouseEvent>
#include <QSvgRenderer>
#include <QDebug>
#include <QXmlStreamReader>
#include <QFile>
#include <QDomDocument>
#include <QStringList>

class SVGHandleEvent : public QGraphicsSvgItem {
Q_OBJECT

public:
    explicit SVGHandleEvent(const QString &svgFilePath, const QString &elementId, QGraphicsItem* parent = nullptr);
    void setScaleAndPosition(qreal scale, qreal x, qreal y);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QString getElementIdAtPosition(const QPointF &position);
    QStringList getElementIdsFromSvg(const QString &filePath);
    bool matchesPosition(const QDomElement &element, const QPointF &position);

    QString svgFilePath;
    QString elementId;
    QSvgRenderer *renderer;
};

#endif // CLICKABLESVGITEM_H