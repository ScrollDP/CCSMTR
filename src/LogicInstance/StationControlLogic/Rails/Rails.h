#ifndef CCSMTR_RAILS_H
#define CCSMTR_RAILS_H
#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QLabel>
#include "../Actions/RailsAction.h"

class RailsAction;

class Rails : public QObject {

public:
    explicit Rails();
    ~Rails() override;

    QGraphicsScene* railsSceneGraphic= new QGraphicsScene();
    // Add the turnout item
    int idLoad = 0;
    static bool updateTurnoutInXml(int idLine, bool switchTurnout);
    bool loadFromXmlTurnouts(int id, const QString& string);
    void deleteLinesWithId(int id) const;
    static const QString fileName;

private:
    QMap<int, QGraphicsItemGroup*> turnoutGroups;

    void addLine(int x1, int y1, int x2, int y2, QColor color, int turnoutId, bool switchTurnout);
    void addTurnoutToScene(int id, int x1, int y1, QColor color, double angleTurnout, bool switchTurnout, bool flipped, bool mirror);
    bool firstLoad = true;
    bool loadFromXmlRails();

    void
    addTurnoutToSceneANG(int idLine, int x1, int y1, QColor color, double angleTurnout, bool switchTurnout,
                         bool flipped,
                         bool mirror);
};


#endif //CCSMTR_RAILS_H
