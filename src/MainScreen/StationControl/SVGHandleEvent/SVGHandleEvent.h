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
#include <thread>
#include "../../TabFolder/ConnectionTab/DCC-EX/CommandQueue.h"

class SVGHandleEvent : public QGraphicsSvgItem {
Q_OBJECT

    std::thread vyhybkaThread, vyhybkaThreadGroupTurnout, checkTurnoutsThread, colorBackgroundThread;
    std::mutex mtx_toggle_vyhybka, mtx_toggle_vyhybka_group_turnout, mtx_check_turnouts, mtx_color_background;

public:
    explicit SVGHandleEvent(const QString &svgFilePath, QString elementId, int row, int col, bool flipped, int rotate, QGraphicsItem* parent = nullptr);
    ~SVGHandleEvent() override;

    void setScaleAndPosition(qreal scale, qreal x, qreal y);
    void updateTransform(const QString &transformStr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:

    void vyhybkaMenu(const QPoint &pos, const QString &id);
    void threadToggleVyhybka(bool straight, bool diverging, const QString &path, const QString &elementId);
    void toggleVisibility(bool straight, bool diverging, const QString &path, const QString &elementId);


    void hlavneNavestidloMenu(const QPoint &pos, const QString &id);
    void vlakovaCestaRouteVC(const QString &elementid);
    void stavanieVCCesty(const QString &elementid);

    void zriadovacieNavestidloMenu(const QPoint &pos, const QString &id);
    void vlakovaCestaRoutePC();
    void stavaniePCCesty(const QString &elementid);


    QString getElementIdAtPosition(const QPointF &position);
    QStringList getElementIdsFromSvg(const QString &filePath);


    void saveAndReload(const QDomDocument& doc, const QString& path, const QString& elementId);
    void reloadSVG(const QString &reloadPath,const QString &elemID);
    void changeBackgroundColor(const QString &path, const QString &elementId);
    void changeElementColor(const QString &path, const QString &elementId);

    void threadChangeBackgroundColor(const QString &path, const QString &elementId);

    static void sendToArduino(const QString &dataList);

    QString startPointElementId;
    QString svgFilePath;
    QString elementId;
    QSvgRenderer *renderer;
    int row;
    int col;
    bool flipped;
    int rotate;

    static QString getTurnoutSvgPath(const QString &turnoutId);

    void toggleVyhybkaInGroup(bool straight, bool diverging, const QString &path, const QString &turnoutID);

    void threadToggleVyhybkaGroupTurnout(bool straight, bool diverging, const QString &path, const QString &elementId);

    static void rusenieCesty(const QString &elementid);



    bool checkTurnouts(const QString &routeName, const QString &m_id);

    bool threadCheckTurnouts(const QString &routeName, const QString &m_id);

};

#endif // CLICKABLESVGITEM_H