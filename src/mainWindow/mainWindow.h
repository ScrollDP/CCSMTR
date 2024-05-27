#ifndef CCSMTR_MAINWINDOW_H
#define CCSMTR_MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "../connection/DCC-EX/dccEx.h" // Include the dccEx.h file
#include "../connection/Intelibox_I/intelibox_I.h" // Include the intelibox_I.h file
#include "../Throttle/ThrottleWindow.h" // Include the ThrottleWindow.h file

class mainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = nullptr);
    ~mainWindow() override;

    static bool isAnyConnected; // Add a static boolean variable to check if any connection is active

protected:
    void closeEvent(QCloseEvent *event) override; // Override the closeEvent method

private slots:
    void onActionDCC_EXTriggered(); // Add a slot for the actionDCC_EX triggered signal
    void onActionIntelibox_ITriggered(); // Add a slot for the actionIntelibox_I triggered signal
    void onActionThrottleTriggered(); // Add a slot for the actionThrottle triggered signal

private:
    Ui::MainWindow ui{};
    dccEx *dccExWindow; // Add a pointer to a dccEx window
    intelibox_I *intelibox_IWindow; // Add a pointer to an Intelibox_I window

};

#endif //CCSMTR_MAINWINDOW_H