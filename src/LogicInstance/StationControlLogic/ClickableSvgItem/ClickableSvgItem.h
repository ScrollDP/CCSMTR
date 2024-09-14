#ifndef CLICKABLESVGITEM_H
#define CLICKABLESVGITEM_H

#include <QGraphicsSvgItem>
#include <QGraphicsSceneMouseEvent>

class ClickableSvgItem : public QGraphicsSvgItem {
Q_OBJECT

public:
    explicit ClickableSvgItem(const QString &fileName, QGraphicsItem *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    bool stateAVisible;
    QString fileName; // Add this member variable
    void toggleTurnoutState(const QString &clickedId);
    QMap<QString, QRectF> elementBoundingBoxes;
};

#endif // CLICKABLESVGITEM_H