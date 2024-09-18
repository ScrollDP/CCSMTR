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
#include "../../../MainScreen/TabFolder/ConnectionTab/DCC-EX/CommandQueue.h"

class SVGHandleEvent : public QGraphicsSvgItem {
Q_OBJECT

public:
    explicit SVGHandleEvent(const QString &svgFilePath, QString elementId, int row, int col, bool flipped, int rotate, QGraphicsItem* parent = nullptr);
    void setScaleAndPosition(qreal scale, qreal x, qreal y);

    void updateTransform(const QString &transformStr);


protected:
    [[maybe_unused]] void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    [[maybe_unused]] QString getElementIdAtPosition(const QPointF &position);
    QStringList getElementIdsFromSvg(const QString &filePath);

    QString svgFilePath;
    QString elementId;
    QSvgRenderer *renderer;
    int row;
    int col;
    bool flipped;
    int rotate;
    std::mutex mtx_vyhybka_menu,mtx_toggle_vyhybka;


    void toggleVisibility(bool straight, bool diverging);
    void threadVyhybkaMenu(const QPoint &pos, const QString &id);
    void threadToggleVyhybka(bool straight, bool diverging);

    void reloadSVG();

    void changeColor(bool rightClick, bool middleClick);

    bool rightclicked{}, middleclicked{};

    void vyhybkaMenu(const QPoint &pos, const QString &id);
    static void hlavneNavestidloMenu(const QPoint &pos, const QString &id);
    static void zriadovacieNavestidloMenu(const QPoint &pos, const QString &id);


    void saveAndReload(const QDomDocument& doc);

    static void sendToArduino(const QString &dataList);
};

#endif // CLICKABLESVGITEM_H