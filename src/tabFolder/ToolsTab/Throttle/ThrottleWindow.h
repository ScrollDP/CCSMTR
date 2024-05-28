#ifndef THROTTLEWINDOW_H
#define THROTTLEWINDOW_H

#include <QMainWindow>
#include "ui_ThrottleWindow.h" // Include the UI header file
#include "../../connectionTab/DCC-EX/dccEx.h"

class ThrottleWindow : public QMainWindow {
Q_OBJECT

public:
    explicit ThrottleWindow(QWidget *parent = nullptr, dccEx *dccExInstance = nullptr); // Add a pointer to a dccEx window
    ~ThrottleWindow() override;

private slots:
    void onReleaseButtonClicked();
    void onAquireButtonClicked();
    void onSpeedSliderValueChanged(int value,dccEx *dccExInstance);
    void onFunctionButtonClicked(dccEx *dccExInstance);

private:
    Ui::ThrottleWindow *ui;
    int direction = 1;
    int FRspeed = 0; // TODO: skúsiť zmeniť na 0 na -1 pri testoch
    QMap<QString, int> functionButtonStates;

    void onForwardButtonClicked(dccEx *dccExInstance);
    void onReverseButtonClicked(dccEx *dccExInstance);
    void setDirection(int dir, dccEx *dccExInstance);
    static void sendToArduino(const QString &dataList, dccEx *dccExInstance);
    void setButtonsEnabled(bool enabled);
    void connectButtons(dccEx *dccExInstance);
};

#endif // THROTTLEWINDOW_H