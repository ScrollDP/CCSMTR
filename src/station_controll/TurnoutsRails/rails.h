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
    void addLineToScene(int x1, int y1, int x2, int y2, QColor color) const;
    void addLineWithTurn(int x1, int y1, int x2, int y2, QColor color, int turnLength, int angle);
    void addLineWithTurnMirror(int x1, int y1, int x2, int y2, QColor color, int turnLength, int angle);
    void addLineWithFlipped(int x1, int y1, int x2, int y2, QColor color, int turnLength, int angle);
    void addLineWithFlippedMirror(int x1, int y1, int x2, int y2, QColor color, int turnLength, int angle);


};


#endif //CCSMTR_RAILS_H
