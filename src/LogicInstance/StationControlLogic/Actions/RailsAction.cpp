#include "RailsAction.h"

RailsAction::RailsAction(int x1, int y1, int x2, int y2, int turnoutId, bool switchTurnout, Rails* rails)
        : QGraphicsLineItem(x1, y1, x2, y2), m_turnoutId(turnoutId), m_switchedTurnout(switchTurnout),rails(rails) {

    //checkBool();
}

RailsAction::~RailsAction() = default;
/*
void RailsAction::checkBool() {

    if(m_editMode){
        qDebug() << "editMode check is true";
    }
    else{
        qDebug() << "editMode check is false";
    }

}*/

void RailsAction::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    // Check if the item is in the scene before removing it
    if (!editMode && scene() == rails->railsSceneGraphic && event->button() == Qt::LeftButton) {
        qDebug() << "editMode is false" << editMode;
        qDebug() << "Stlacena line: " << m_turnoutId;

        // Load the current state of the turnout from the XML file
        bool currentState = Rails::updateTurnoutInXml(m_turnoutId, m_switchedTurnout);

        // Switch the state of the turnout
        bool newState = !currentState;

        // Update the turnout in the XML file with the new state
        Rails::updateTurnoutInXml(m_turnoutId, newState);

        // Update m_switchedTurnout based on the new state
        m_switchedTurnout = newState;
        //dont remove if they are with darkgray color
        if(scene() == rails->railsSceneGraphic && pen().color() == QColor(Qt::darkGray)){
            //show position of line
            //QLineF line = this->line();
            //QPointF startPoint = line.p1();
            //QPointF endPoint = line.p2();
            //qDebug() << "Start position: (" << startPoint.x() << ", " << startPoint.y() << ")";
            //qDebug() << "End position: (" << endPoint.x() << ", " << endPoint.y() << ")";
            //return;
        }
        else{
            rails->deleteLinesWithId(m_turnoutId);
        }
        //qDebug() << "item is in the scene";
        // Load the updated turnout from the XML file
        rails->loadFromXmlTurnouts(m_turnoutId, Rails::fileName);
        //qDebug() << "new id:" << m_turnoutId <<" switch:"<< m_switchedTurnout;
    }
    else {
        qDebug() << "editMode is true 1" << editMode;
        qDebug() << "Left click in editmode error";

        // Create a new pen with a wide width and a color that stands out
        QPen glowPen;
        glowPen.setWidth(15);
        glowPen.setColor(Qt::yellow);

        // Set the pen of the QGraphicsLineItem to the new pen
        std::shared_ptr<QPen> pen = std::make_shared<QPen>(glowPen);

        //this->setPen(glowPen);


        // Iterate over all items in the scene
        QGraphicsScene* currentScene = scene();
        if (currentScene) {
            for (QGraphicsItem* item : currentScene->items()) {
                // Check if the item is a RailsAction
                auto* railsAction = dynamic_cast<RailsAction*>(item);
                if (railsAction) {
                    // If the id of the item matches the id of the clicked item, change its color
                    if (railsAction->getTurnoutId() == this->getTurnoutId()) {
                        railsAction->setPen(glowPen);
                    }
                }
            }
        }
        //Event for right click if it is rigtbutton or id turnout is from 1-30
        qDebug() << "editMode before 2" << editMode;
        if(scene() == rails->railsSceneGraphic && event->button() == Qt::RightButton) {
            qDebug() << "editMode is true 2" << editMode;
            if(m_turnoutId <= 30 && m_turnoutId > 0){

                qDebug() << "Right click" << m_turnoutId;
                RightClick dialog;
                dialog.loadTurnout(m_turnoutId);
                dialog.exec();
                if(dialog.saveTurnout()) {
                    rails->deleteLinesWithId(m_turnoutId);
                    rails->loadFromXmlTurnouts(m_turnoutId, Rails::fileName);
                }
            }else{return;}

        }
    }



}


int RailsAction::getTurnoutId() const {
    return m_turnoutId;
}
