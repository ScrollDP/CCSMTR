#ifndef MOUSEEVENTHANDLER_H
#define MOUSEEVENTHANDLER_H

#include <QGraphicsSceneMouseEvent>
#include <QString>
#include <QDebug>
#include "SVGHandleEvent.h" // Include the header for SVGHandleEvent

class SVGHandleEvent; // Forward declaration

class MouseEventHandler {
public:
    static void handleMousePressEvent(QGraphicsSceneMouseEvent *event, const QString &elementId);

private:
    static QString firstClickedElementId;
    SVGHandleEvent* svgHandleEvent; // Declare svgHandleEvent

};

#endif // MOUSEEVENTHANDLER_H