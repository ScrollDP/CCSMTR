#include "RailsAction.h"


RailsAction::RailsAction(int x1, int y1, int x2, int y2, int turnoutId, bool switchTurnout, Rails* rails)
        : QGraphicsLineItem(x1, y1, x2, y2), m_turnoutId(turnoutId), m_switchedTurnout(switchTurnout),rails(rails) {}

RailsAction::~RailsAction() = default;
/*
void RailsAction::mousePressEvent(QGraphicsSceneMouseEvent* event) {

    // Update the turnout in the XML file and get the new state
    bool newState = rails->updateTurnoutInXml(m_turnoutId, !m_switchedTurnout);
    qDebug() << "old id:" << m_turnoutId <<" switch:"<< m_switchedTurnout;
    //qDebug() << "newState:" << newState;
    // Update m_switchedTurnout based on the new state
    m_switchedTurnout = newState;

    // Load the updated turnout from the XML file
    rails->loadFromXml(m_turnoutId, "turnouts.xml");

    qDebug() << "new id:" << m_turnoutId <<" switch:"<< m_switchedTurnout;
}*/

void RailsAction::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    // Remove the old line from the scene

    scene()->removeItem(this);


    // Update the turnout in the XML file and get the new state
    bool newState = rails->updateTurnoutInXml(m_turnoutId, !m_switchedTurnout);

    // Update m_switchedTurnout based on the new state
    m_switchedTurnout = newState;

    // Load the updated turnout from the XML file
    rails->loadFromXml(m_turnoutId, "turnouts.xml");

    qDebug() << "new id:" << m_turnoutId <<" switch:"<< m_switchedTurnout;
}
