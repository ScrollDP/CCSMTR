#ifndef CLICKABLESVGITEM_H
#define CLICKABLESVGITEM_H

#include <QGraphicsSvgItem>
#include <QGraphicsSceneMouseEvent>
#include <QSvgRenderer>
#include <QDebug>
#include <QXmlStreamReader>
#include <QFile>

class ClickableSvgItem : public QGraphicsSvgItem {
Q_OBJECT

public:
    explicit ClickableSvgItem(QGraphicsItem* parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QString getElementIdAtPosition(const QPointF& position);
    QStringList getElementIdsFromSvg(const QString& filePath);
};

#endif // CLICKABLESVGITEM_H