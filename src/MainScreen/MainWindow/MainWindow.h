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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void toggleFullScreen();

    static bool isAnyConnected;

    Ui_MainWindow *ui;

    bool edit{};

private slots:
    void onActionDCC_EXTriggered();
    void onActionThrottleTriggered();
    void onActionPowerTriggered();

private:

    StationControl *stationControllWindow;
    DccEx *dccExWindow;
    PowerWindow *powerWindow;

    void keyPressEvent(QKeyEvent *event) override;


protected:
    void closeEvent(QCloseEvent *event) override;

    bool eventFilter(QObject *watched, QEvent *event) override;

    void toggleTabShow() const;

    void editMenuEnabled();
};

#endif //CCSMTR_MAINWINDOW_H