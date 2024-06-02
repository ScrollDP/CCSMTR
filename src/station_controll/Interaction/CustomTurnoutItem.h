// CustomTurnoutItem.h
#ifndef CCSMTR_CUSTOMTURNOUTITEM_H
#define CCSMTR_CUSTOMTURNOUTITEM_H
#include <QGraphicsObject>
#include <QPainter>
#include "CustomLineItem.h"

class CustomTurnoutItem : public QGraphicsObject {
Q_OBJECT

public:
    CustomTurnoutItem(int id, bool flipped, bool mirror, double angleTurnout, QGraphicsItem* parent = nullptr)
            : QGraphicsObject(parent), m_id(id), m_flipped(flipped), m_mirror(mirror), m_angleTurnout(angleTurnout) {
        m_label = new QGraphicsTextItem(this);
        setLabel(QString::number(m_id));
}

    void setLabel(const QString& text) {
        m_label->setPlainText(text);
    }

    QRectF boundingRect() const override {
        if (m_flipped && m_mirror) {
            // Return a rectangle for the flipped case
            return QRectF(0, 0, -20, -20);
        } else if (m_mirror) {
            // Return a rectangle for the mirrored case
            return QRectF(0, 0, -20, 20);
        }
        else if (m_flipped) {
            // Return the default rectangle
            return QRectF(0, 0, 20, 20);
        }
        else {
            // Return the default rectangle
            return QRectF(0, 0, 20, -20);
        }
    }



    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override {
        // Paint the item. This is just an example, modify it as needed.
        painter->drawRect(boundingRect());

        // Position the label in the middle of the bounding rectangle
        m_label->setPos(boundingRect().center() - QPointF(m_label->boundingRect().width() / 2, m_label->boundingRect().height() / 2));
    }


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        qDebug() << "Turnout clicked: " << m_id;
        QGraphicsObject::mousePressEvent(event);
    }

private:
    int m_id;
    bool m_flipped;
    bool m_mirror;
    QGraphicsTextItem* m_label;
    double m_angleTurnout;
};

#endif //CCSMTR_CUSTOMTURNOUTITEM_H