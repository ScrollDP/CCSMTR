// CustomLineItem.cpp
#include "CustomLineItem.h"
#include <QPen>

CustomLineItem::CustomLineItem(int x1, int y1, int x2, int y2) : QGraphicsLineItem(x1, y1, x2, y2) {}

void CustomLineItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    //setPen(QPen(Qt::red, pen().width(),Qt::SolidLine, Qt::MPenCapStyle, Qt::MPenJoinStyle));
    qDebug() << "Line clicked";
}