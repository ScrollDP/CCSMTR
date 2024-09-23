#include "MouseEventHandler.h"
#include <QRegularExpression>
#include "SVGHandleEvent.h"

SVGHandleEvent* MouseEventHandler::svgHandleEvent = nullptr;

void MouseEventHandler::handleMousePressEvent(QGraphicsSceneMouseEvent *event, const QString &elementId) {
    if(event->button() == Qt::LeftButton) {
        if (QRegularExpression("^HN\\d+$").match(elementId).hasMatch()) {
            svgHandleEvent->vlakovaCestaRouteVC(elementId);
            return;
        }

        svgHandleEvent->threadStavanieVCCesty(elementId);
        svgHandleEvent->threadStavaniePCCesty(elementId);
    }
    if(event->button() == Qt::MiddleButton) {
        if (QRegularExpression("^HN\\d+$").match(elementId).hasMatch()) {
            svgHandleEvent->hlavneNavestidloMenu(event->screenPos(), elementId);
        } else if(QRegularExpression("^T\\d+(_\\d+)?$").match(elementId).hasMatch()) {
            svgHandleEvent->vyhybkaMenu(event->screenPos(), elementId);
        } else if(QRegularExpression("^ZN\\d+$").match(elementId).hasMatch()) {
            svgHandleEvent->zriadovacieNavestidloMenu(event->screenPos(), elementId);
        }
    }
    if(event->button() == Qt::RightButton) {
        if(QRegularExpression("^ZN\\d+?$").match(elementId).hasMatch()) {
            svgHandleEvent->vlakovaCestaRoutePC();
        } else if(QRegularExpression("^HN\\d+?$").match(elementId).hasMatch()) {
            svgHandleEvent->vlakovaCestaRoutePC();
        }
    }
    if(event->button() == Qt::LeftButton && event->modifiers() == Qt::ControlModifier) {
        svgHandleEvent->rusenieCesty(elementId);
    }
}