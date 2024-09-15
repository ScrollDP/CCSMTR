#include "SVGHandleEvent.h"
#include <QSvgRenderer>
#include <QGraphicsScene>
#include <QDomDocument>
#include <QFile>
#include <QDebug>
#include <QRegularExpression>

SVGHandleEvent::SVGHandleEvent(QGraphicsItem* parent)
        : QGraphicsSvgItem(parent) {
}
