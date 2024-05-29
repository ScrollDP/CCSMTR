#ifndef CCSMTR_RAILS_H
#define CCSMTR_RAILS_H
#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsScene>
#include "../ClickLineEvent.h"
class rails {

public:
    explicit rails();
    ~rails();

    QGraphicsScene* railsSceneGraphic= new QGraphicsScene();

private:


};


#endif //CCSMTR_RAILS_H
