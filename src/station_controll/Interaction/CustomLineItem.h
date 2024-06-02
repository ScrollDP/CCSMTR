#ifndef CCSMTR_CUSTOMLINEITEM_H
#define CCSMTR_CUSTOMLINEITEM_H
// CustomLineItem.h
#include <QGraphicsLineItem>

class CustomLineItem : public QGraphicsLineItem {
public:
    CustomLineItem(int x1, int y1, int x2, int y2);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif //CCSMTR_CUSTOMLINEITEM_H
