#include "RailsAction.h"


RailsAction::RailsAction(int x1, int y1, int x2, int y2, int turnoutId, bool switchTurnout, Rails* rails)
        : QGraphicsLineItem(x1, y1, x2, y2), m_turnoutId(turnoutId), m_switchedTurnout(switchTurnout),rails(rails) {}

RailsAction::~RailsAction() = default;


void RailsAction::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    qDebug() << "mousePressEvent" << m_turnoutId;

    // Load the current state of the turnout from the XML file
    bool currentState = rails->updateTurnoutInXml(m_turnoutId, m_switchedTurnout);

    // Switch the state of the turnout
    bool newState = !currentState;

    // Update the turnout in the XML file with the new state
    rails->updateTurnoutInXml(m_turnoutId, newState);

    // Update m_switchedTurnout based on the new state
    m_switchedTurnout = newState;

    // Check if the item is in the scene before removing it
    if (scene() == rails->railsSceneGraphic) {
        rails->deleteLinesWithId(m_turnoutId);
        //rails->railsSceneGraphic->removeItem(this);
        //update();
        qDebug() << "item is in the scene";
    } else {
        qDebug() << "item is not in the scene";
    }

    // Load the updated turnout from the XML file
    rails->loadFromXml(m_turnoutId, "turnouts.xml");

    qDebug() << "new id:" << m_turnoutId <<" switch:"<< m_switchedTurnout;
}

int RailsAction::getTurnoutId() const {
    return m_turnoutId;
}
