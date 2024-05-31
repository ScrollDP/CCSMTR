#ifndef CCSMTR_RAILS_H
#define CCSMTR_RAILS_H
#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QLabel>

class rails {

public:
    explicit rails();
    ~rails();

    QGraphicsScene* railsSceneGraphic= new QGraphicsScene();

private:

    void setupScene();
    void addLine(int x1, int y1, int x2, int y2, QColor color) const;
    void addTurnoutToScene(int x1, int y1, QColor color, double angleTurnout, bool switchTurnout, bool flipped, bool mirror) const;
};


#endif //CCSMTR_RAILS_H
