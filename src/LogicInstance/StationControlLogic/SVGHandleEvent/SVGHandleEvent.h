#ifndef CLICKABLESVGITEM_H
#define CLICKABLESVGITEM_H

#include <QGraphicsSvgItem>
#include <QGraphicsSceneMouseEvent>
#include <QSvgRenderer>
#include <QDebug>
#include <QXmlStreamReader>
#include <QFile>
#include <QDomDocument>
#include <QStringList>

class SVGHandleEvent : public QGraphicsSvgItem {
Q_OBJECT

public:
    explicit SVGHandleEvent(const QString &svgFilePath, QString elementId, QGraphicsItem* parent = nullptr);
    void setScaleAndPosition(qreal scale, qreal x, qreal y);

protected:
    [[maybe_unused]] void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    [[maybe_unused]] QString getElementIdAtPosition(const QPointF &position);
    QStringList getElementIdsFromSvg(const QString &filePath);

    QString svgFilePath;
    QString elementId;
    QSvgRenderer *renderer;

    void toggleVisibility();
};

#endif // CLICKABLESVGITEM_H