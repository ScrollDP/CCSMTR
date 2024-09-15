#ifndef CLICKABLESVGITEM_H
#define CLICKABLESVGITEM_H

#include <QGraphicsSvgItem>
#include <QGraphicsSceneMouseEvent>
#include <QSvgRenderer>
#include <QDebug>
#include <QXmlStreamReader>
#include <QFile>
#include <QDomDocument>

class ClickableSvgItem : public QGraphicsSvgItem {
Q_OBJECT

public:
    explicit ClickableSvgItem(QGraphicsItem* parent = nullptr);

    void initialize();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:

    void loadGridLayout(const QString &layoutFilePath);

    QString getElementIdAtPosition(const QPointF& position);

};

#endif // CLICKABLESVGITEM_H