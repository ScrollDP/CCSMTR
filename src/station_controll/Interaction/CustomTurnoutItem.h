#ifndef CCSMTR_CUSTOMTURNOUTITEM_H
#define CCSMTR_CUSTOMTURNOUTITEM_H
// CustomTurnoutItem.h
#include <QGraphicsItem>
#include <QObject>

class CustomTurnoutItem : public QObject, public QGraphicsItem {
Q_OBJECT

public:
    CustomTurnoutItem(int x1, int y1, int x2, int y2);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

signals:
    void turnoutClicked();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    int x1, y1, x2, y2;
    bool switchTurnout;
};


#endif //CCSMTR_CUSTOMTURNOUTITEM_H
