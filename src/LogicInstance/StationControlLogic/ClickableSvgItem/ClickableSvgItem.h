#ifndef CLICKABLESVGITEM_H
#define CLICKABLESVGITEM_H

#include <QGraphicsSvgItem>
#include <QGraphicsSceneMouseEvent>
#include <QSvgRenderer>
#include <QDebug>
#include <QXmlStreamReader>
#include <QFile>
#include <QDomDocument>

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
    void toggleVisibility(const QString& groupId, const QString& elementId1, const QString& elementId2);
    QDomDocument loadSvgDocument();
};

#endif // CLICKABLESVGITEM_H