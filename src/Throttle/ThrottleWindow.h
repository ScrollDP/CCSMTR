#ifndef THROTTLEWINDOW_H
#define THROTTLEWINDOW_H

#include <QMainWindow>
#include "ui_ThrottleWindow.h" // Include the UI header file
#include "../connection/DCC-EX/dccEx.h"


class ThrottleWindow : public QMainWindow {
Q_OBJECT

public:
    explicit ThrottleWindow(QWidget *parent = nullptr, dccEx *dccExInstance = nullptr); // Add a pointer to a dccEx window

    ~ThrottleWindow() override;

    // Add your methods here
private slots:

    void onReleaseButtonClicked();

    void onAquireButtonClicked();

    void onSpeedSliderValueChanged(int value,dccEx *dccExInstance);


private:
    Ui::ThrottleWindow *ui; // Add this line
    int direction = 1;
    int FRspeed = 0; // TODO: skúsiť zmeniť na 0 na -1 pri testoch
    void onForwardButtonClicked(dccEx *dccExInstance);


    void onReverseButtonClicked(dccEx *dccExInstance);

    static void sendToArduino(const QString &dataList, dccEx *dccExInstance) ;



};


#endif // THROTTLEWINDOW_H