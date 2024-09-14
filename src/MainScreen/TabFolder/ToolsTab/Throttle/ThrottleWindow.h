#ifndef THROTTLEWINDOW_H
#define THROTTLEWINDOW_H

#include <QMainWindow>
#include "ui_ThrottleWindow.h"
#include "../../ConnectionTab/DCC-EX/DccEx.h"

class DccEx;

class ThrottleWindow : public QMainWindow {
Q_OBJECT

public:
    explicit ThrottleWindow(QWidget *parent = nullptr, DccEx *dccExInstance = nullptr); // Add a pointer to a dccEx window
    ~ThrottleWindow() override;

private slots:
    void onReleaseButtonClicked();
    void onAquireButtonClicked();
    void onSpeedSliderValueChanged(int value,DccEx *dccExInstance);
    void onFunctionButtonClicked(DccEx *dccExInstance);

private:
    Ui_ThrottleWindow *ui;
    int direction = 1;
    int FRspeed = 0; // TODO: skúsiť zmeniť na 0 na -1 pri testoch
    QMap<QString, int> functionButtonStates;

    void onForwardButtonClicked(DccEx *dccExInstance);
    void onReverseButtonClicked(DccEx *dccExInstance);
    void setDirection(int dir, DccEx *dccExInstance);
    static void sendToArduino(const QString &dataList, DccEx *dccExInstance);
    void setButtonsEnabled(bool enabled);
    void connectButtons(DccEx *dccExInstance);

    [[maybe_unused]] void keyPressEvent(QKeyEvent *event) override;

};

#endif // THROTTLEWINDOW_H