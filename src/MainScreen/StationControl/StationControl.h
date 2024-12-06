#ifndef CCSMTR_STATIONCONTROL_H
#define CCSMTR_STATIONCONTROL_H

#include "ui_stationControl.h"
#include <QWidget>
#include <QDomDocument>
#include <QGraphicsSvgItem>
#include "SVGHandleEvent/SVGHandleEvent.h"

class StationControl : public QWidget {
Q_OBJECT

public:
    explicit StationControl(QWidget *parent = nullptr, const QString &svgFilePath = "../layout/layout.xml");
    ~StationControl() override;
    Ui::StationControl *ui;

private:
    void LoadingSvgFile();
    void ResetRoutes();

    int Scale = 4;
    int Position_Col = 8;
    int Position_Row = 12;

    void ApplyTransformation(bool mirror, int rotate, SVGHandleEvent* svgHandleEvent, const QString& type);
    QSvgRenderer *renderer;
    QString svgFilePath;

    void createTurnoutConfigFile(const QString &filePath, const QString &status, const QString &type);

    QString loadTurnoutStatusFromConfigFile(const QString &turnoutID);
};


#endif //CCSMTR_STATIONCONTROL_H