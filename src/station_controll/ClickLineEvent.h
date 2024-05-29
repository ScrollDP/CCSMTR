#ifndef CCSMTR_CLICKLINEEVENT_H
#define CCSMTR_CLICKLINEEVENT_H

#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPen>

class ClickLineEvent : public QGraphicsLineItem {
public:
    using QGraphicsLineItem::QGraphicsLineItem;  // inherit constructors

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override{

        QPointF clickPosition = event->pos();
        qDebug() << "Line clicked at position:" << clickPosition;

        QPen pen = this->pen();
        pen.setColor(Qt::yellow);
        this->setPen(pen);

        QGraphicsLineItem::mousePressEvent(event);  // propagate the event further
    }
};

#endif //CCSMTR_CLICKLINEEVENT_H
