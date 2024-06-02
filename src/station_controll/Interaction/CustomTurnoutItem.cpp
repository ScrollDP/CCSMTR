// CustomTurnoutItem.cpp
#include "CustomTurnoutItem.h"
#include <QPainter>
#include <QDebug>

CustomTurnoutItem::CustomTurnoutItem(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2), switchTurnout(false) {}

QRectF CustomTurnoutItem::boundingRect() const {
    return QRectF(x1, y1, abs(x2 - x1), abs(y2 - y1));
}

void CustomTurnoutItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Draw the turnout
    QPen pen(switchTurnout ? Qt::green : Qt::black, 2);
    painter->setPen(pen);
    painter->drawLine(x1, y1, x2, y2);
    painter->drawEllipse(QPoint((x1 + x2) / 2, (y1 + y2) / 2), 10, 10);
}

void CustomTurnoutItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    // Switch the turnout when it's clicked
    switchTurnout = !switchTurnout;

    // Log the switch state
    qDebug() << "Turnout clicked. Switch state is now: " << (switchTurnout ? "ON" : "OFF");

    // Emit the turnoutClicked signal
    emit turnoutClicked();

    // Redraw the item
    update();
}