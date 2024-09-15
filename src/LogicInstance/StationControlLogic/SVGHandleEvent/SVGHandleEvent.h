#ifndef CLICKABLESVGITEM_H
#define CLICKABLESVGITEM_H

#include <QGraphicsSvgItem>
#include <QGraphicsSceneMouseEvent>
#include <QSvgRenderer>
#include <QDebug>
#include <QXmlStreamReader>
#include <QFile>
#include <QDomDocument>

class SVGHandleEvent : public QGraphicsSvgItem {
Q_OBJECT

public:
    explicit SVGHandleEvent(QGraphicsItem* parent = nullptr);

protected:


private:



};

#endif // CLICKABLESVGITEM_H