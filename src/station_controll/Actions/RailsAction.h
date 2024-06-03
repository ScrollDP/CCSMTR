// RailsAction.h
#ifndef CCSMTR_RAILSACTION_H
#define CCSMTR_RAILSACTION_H
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include "../Rails/Rails.h"

class Rails;


class RailsAction : public QGraphicsLineItem {
public:
    RailsAction(int x1, int y1, int x2, int y2, int turnoutId, bool switchTurnout, Rails* rails);
    ~RailsAction() override;
    int getTurnoutId() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    int m_turnoutId;
    bool m_switchedTurnout;
    Rails *rails;
};

#endif //CCSMTR_RAILSACTION_H