#ifndef CLICKABLESVGITEM_H
#define CLICKABLESVGITEM_H

#include <QGraphicsSvgItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

class ClickableSvgItem : public QGraphicsSvgItem {
Q_OBJECT

public:
    explicit ClickableSvgItem(QGraphicsItem* parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // CLICKABLESVGITEM_H