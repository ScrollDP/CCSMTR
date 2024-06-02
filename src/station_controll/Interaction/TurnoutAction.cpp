#include "TurnoutAction.h"
#include <QGraphicsLineItem>

TurnoutAction::TurnoutAction(int id, bool flipped, bool mirror, double angleTurnout, bool switchedTurnout, QGraphicsItem* parent)
        : QGraphicsObject(parent), m_id(id), m_flipped(flipped), m_mirror(mirror), m_angleTurnout(angleTurnout), m_switchedTurnout(switchedTurnout) {
    m_label = new QGraphicsTextItem(this);
    setLabel(QString::number(m_id));
}

void TurnoutAction::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    qDebug() << "Turnout clicked: " << m_id;

    auto* rails = new Rails(); // rails is now pointing to a valid Rails object
    // Update the turnout in the XML file and get the new state
    bool newState = rails->updateTurnoutInXml(m_id, !m_switchedTurnout);

    if (newState) {
        setLabel(QString::number(m_id) + "\nSwitched"); // Add a second line to the label
    } else {
        setLabel(QString::number(m_id)); // Remove the second line from the label
    }

    // Update m_switchedTurnout based on the new state
    m_switchedTurnout = newState;

    //this->update(); // Update the item to reflect the new state

    rails->loadFromXml(m_id, "turnouts.xml"); // This should work fine now
    qDebug() << "id:" << m_id <<" switch:"<< m_switchedTurnout;
    QGraphicsObject::mousePressEvent(event);
}

void TurnoutAction::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)  {
    if (m_switchedTurnout) {
    // Draw the turnout differently when it is switched
    painter->setBrush(Qt::green); // For example, change the color to green
    } else {
    painter->setBrush(Qt::black); // Use the default color when the turnout is not switched
    }
    //drawRect but make sure it is not placed on same position as previous Rect
    painter->drawRect(boundingRect());


    // Position the label in the middle of the bounding rectangle
    m_label->setPos(boundingRect().center() - QPointF(m_label->boundingRect().width() / 2, m_label->boundingRect().height() / 2));
}


QRectF TurnoutAction::boundingRect() const  {
    if (m_flipped && m_mirror) {
        // Return a rectangle for the flipped case
        return QRectF(0, 0, -20, -20);
    } else if (m_mirror) {
        // Return a rectangle for the mirrored case
        return QRectF(0, 0, -20, 20);
    } else if (m_flipped) {
        // Return the default rectangle
        return QRectF(0, 0, 20, 20);
    } else {
        // Return the default rectangle
        return QRectF(0, 0, 20, -20);
    }
}

void TurnoutAction::setLabel(const QString& text) {
    m_label->setPlainText(text);
}

TurnoutAction::~TurnoutAction() {
delete m_label;
}