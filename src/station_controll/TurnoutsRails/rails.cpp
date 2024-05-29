#include "rails.h"


rails::rails() {
    struct Line {
        QPointF start, end;
        QColor color;
        int pos;
    };

    Line lines[] = {
            {{0, 0}, {80, 0}, Qt::lightGray, 0},
            {{0, 0}, {30, 0}, Qt::red, 80},
            {{0, 0}, {30, 0}, Qt::green, 110},
            {{0, 0}, {30, 0}, Qt::blue, 140},
            {{0, 0}, {350, 0}, Qt::lightGray, 170},
            {{0, 0}, {30, 0}, Qt::blue, 520},
            {{0, 0}, {30, 0}, Qt::lightGray, 550},
            {{0, 0}, {30, 0}, Qt::green, 580},
            {{0, 0}, {30, 0}, Qt::red, 610},
            {{0, 0}, {80, 0}, Qt::lightGray, 640}
    };

    for (const auto& line : lines) {
        ClickLineEvent *item = new ClickLineEvent(QLineF(line.start, line.end));
        QPen pen;
        pen.setColor(line.color);
        pen.setWidth(8);
        item->setPen(pen);
        item->setPos(line.pos, 0);
        railsSceneGraphic->addItem(item);
    }
}

rails::~rails() {
    delete railsSceneGraphic;
}