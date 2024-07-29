#ifndef CCSMTR_MAINWINDOW_H
#define CCSMTR_MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "../station_controll/stationControll.h" // Include the stationControll.h file
#include "../tabFolder/connectionTab/DCC-EX/dccEx.h" // Include the dccEx.h file
#include "../tabFolder/ToolsTab/Throttle/ThrottleWindow.h" // Include the ThrottleWindow.h file
#include "../tabFolder/connectionTab/Power/PowerWindow.h" // Include the PowerWindow.h file
#include <QTimer>


class mainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = nullptr);
    ~mainWindow() override;

    void toggleFullScreen(); // Add a method to toggle full screen

    static bool isAnyConnected; // Add a static boolean variable to check if any connectionTab is active

    static bool editMode(bool mode);

    bool edit;

private slots:
    void onActionDCC_EXTriggered(); // Add a slot for the actionDCC_EX triggered signal
    void onActionThrottleTriggered(); // Add a slot for the actionThrottle triggered signal
    void onActionPowerTriggered(); // Add a slot for the actionPower triggered signal

private:
    Ui::MainWindow ui{};
    stationControll *stationControllWindow; // Add a pointer to a stationControll window
    dccEx *dccExWindow; // Add a pointer to a dccEx window
    PowerWindow *powerWindow; // Add a pointer to a PowerWindow window

    void keyPressEvent(QKeyEvent *event) override;
    QTimer *hideTimer; // Add a QTimer pointer to hide the tabWidget after a certain time


protected:
    void closeEvent(QCloseEvent *event) override;


    bool eventFilter(QObject *watched, QEvent *event) override;


    void toggleTabShow();
};

#endif //CCSMTR_MAINWINDOW_H