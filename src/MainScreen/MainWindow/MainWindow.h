#ifndef CCSMTR_MAINWINDOW_H
#define CCSMTR_MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QObject>
#include <QCloseEvent>
#include <QPushButton>
#include "ui_MainWindow.h"
#include "../StationControl/StationControl.h"
#include "../TabFolder/ConnectionTab/DCC-EX/DccEx.h"
#include "../TabFolder/ConnectionTab/Power/PowerWindow.h"
#include "../TabFolder/ToolsTab/Throttle/ThrottleWindow.h"

class PowerWindow;

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr); // Add a pointer to a dccEx window
    ~MainWindow() override;

    void toggleFullScreen(); // Add a method to toggle full screen

    static bool isAnyConnected; // Add a static boolean variable to check if any ConnectionTab is active

    static bool editModeFunction(bool mode);

    Ui_MainWindow *ui;

    [[maybe_unused]] bool edit{};

private slots:
    void onActionDCC_EXTriggered(); // Add a slot for the actionDCC_EX triggered signal
    void onActionThrottleTriggered(); // Add a slot for the actionThrottle triggered signal
    void onActionPowerTriggered(); // Add a slot for the actionPower triggered signal

private:

    StationControl *stationControllWindow; // Add a pointer to a StationControl window
    DccEx *dccExWindow; // Add a pointer to a dccEx window
    PowerWindow *powerWindow; // Add a pointer to a PowerWindow window

    [[maybe_unused]] void keyPressEvent(QKeyEvent *event) override;
    QTimer *hideTimer; // Add a QTimer pointer to hide the tabWidget after a certain time


protected:
    [[maybe_unused]] void closeEvent(QCloseEvent *event) override;


    [[maybe_unused]] bool eventFilter(QObject *watched, QEvent *event) override;


    void toggleTabShow() const;

    void editMenuEnabled();
};

#endif //CCSMTR_MAINWINDOW_H