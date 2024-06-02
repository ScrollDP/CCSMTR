#ifndef CCSMTR_RAILS_H
#define CCSMTR_RAILS_H
#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QLabel>
#include "../Interaction/CustomLineItem.h"
#include "../Interaction/CustomTurnoutItem.h"


class rails : public QObject {

public:
    explicit rails();
    ~rails();

    QGraphicsScene* railsSceneGraphic= new QGraphicsScene();

private:

    void setupScene();
    void addLine(int x1, int y1, int x2, int y2, QColor color) const;
    void addTurnoutToScene(int x1, int y1, QColor color, double angleTurnout, bool switchTurnout, bool flipped, bool mirror);
    void loadFromXml(const QString &fileName);

    QString
    turnoutToXml(int startX, int startY, QColor color, double angleTurnout, bool switchTurnout, bool flipped,
                 bool mirror);

    void saveToXml(const QString &fileName, const QString &xmlString);
};


#endif //CCSMTR_RAILS_H
