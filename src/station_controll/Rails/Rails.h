#ifndef CCSMTR_RAILS_H
#define CCSMTR_RAILS_H
#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QLabel>
#include "../Actions/RailsAction.h"


class Rails : public QObject {

public:
    explicit Rails();
    ~Rails() override;

    QGraphicsScene* railsSceneGraphic= new QGraphicsScene();
    // Add the turnout item
    static int id;
    bool updateTurnoutInXml(int id, bool switchTurnout);
    void loadFromXml(int id, const QString &fileName);



private:
    QMap<int, QGraphicsItemGroup*> turnoutGroups;

    void setupScene();
    void addLine(int x1, int y1, int x2, int y2, QColor color, int turnoutId, bool switchTurnout);
    void addTurnoutToScene(int id, int x1, int y1, QColor color, double angleTurnout, bool switchTurnout, bool flipped, bool mirror);


    QString
    turnoutToXml(int startX, int startY, QColor color, double angleTurnout, bool switchTurnout, bool flipped,
                 bool mirror);

    void saveToXml(const QString &fileName, const QString &xmlString);

    bool firstLoad = true;

    bool getSwitchTurnoutState(int turnoutId);

};


#endif //CCSMTR_RAILS_H
