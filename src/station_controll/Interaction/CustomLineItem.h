// CustomLineItem.h
#ifndef CCSMTR_CUSTOMLINEITEM_H
#define CCSMTR_CUSTOMLINEITEM_H
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include "CustomTurnoutItem.h"

class CustomLineItem : public QGraphicsLineItem {
public:
    CustomLineItem(int x1, int y1, int x2, int y2) : QGraphicsLineItem(x1, y1, x2, y2) {

    }


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        // Check if the line is vertical or horizontal
        QLineF line = this->line();
        if (line.dx() == 0 || line.dy() == 0) { // Vertical or horizontal line
            if(pen().color() == Qt::darkGray){
                qDebug() << "Line clicked";
            }

        }
    }

private:

};

#endif //CCSMTR_CUSTOMLINEITEM_H