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

    std::thread vyhybkaThread, hlavneNavestidloThread;
    std::mutex mtx_toggle_vyhybka, mtx_toggle_hlavne_navestidlo;


public:
    explicit SVGHandleEvent(const QString &svgFilePath, QString elementId, int row, int col, bool flipped, int rotate, QGraphicsItem* parent = nullptr);
    ~SVGHandleEvent();
    void setScaleAndPosition(qreal scale, qreal x, qreal y);

    void updateTransform(const QString &transformStr);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QString getElementIdAtPosition(const QPointF &position);
    QStringList getElementIdsFromSvg(const QString &filePath);

    QString svgFilePath;
    QString elementId;
    QSvgRenderer *renderer;
    int row;
    int col;
    bool flipped;
    int rotate;


    void toggleVisibility(bool straight, bool diverging, const QString &path, const QString &elementId);
    void threadToggleVyhybka(bool straight, bool diverging, const QString &path, const QString &elementId);

    void reloadSVG(const QString &reloadPath,const QString &elemID);

    bool rightclicked{}, middleclicked{};

    void vyhybkaMenu(const QPoint &pos, const QString &id);
    void hlavneNavestidloMenu(const QPoint &pos, const QString &id);

    static void zriadovacieNavestidloMenu(const QPoint &pos, const QString &id);


    void saveAndReload(const QDomDocument& doc, const QString& path, const QString& elementId);

    static void sendToArduino(const QString &dataList);

    QString startPointElementId;

    void checkIDwithEndpoint(const QString &elementid);
    void threadHlavneNavestidloMenu();

    void changeColorbackground(const QString &path, const QString &elementId);

    void changingPositionOfTurnouts();

    static QString getTurnoutFilePath(const QString &turnoutId);


    void updateElementById(const QString &elementId);
};

#endif // CLICKABLESVGITEM_H