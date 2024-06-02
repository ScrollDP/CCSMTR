#ifndef CCSMTR_TURNOUTACTION_H
#define CCSMTR_TURNOUTACTION_H

#include <QGraphicsObject>
#include <QPainter>
#include "RailsAction.h"
#include "../Rails/Rails.h"


class TurnoutAction : public QGraphicsObject{
Q_OBJECT

public:
    TurnoutAction(int id, bool flipped, bool mirror, double angleTurnout, bool switchedTurnout, QGraphicsItem* parent = nullptr);
    ~TurnoutAction() override;

    void setLabel(const QString& text);

    QRectF boundingRect() const ;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    int m_id;
    bool m_flipped;
    bool m_mirror;
    QGraphicsTextItem* m_label;
    double m_angleTurnout;
    bool m_switchedTurnout;

};

#endif //CCSMTR_TURNOUTACTION_H
