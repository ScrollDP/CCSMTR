#ifndef POWERWINDOW_H
#define POWERWINDOW_H

#include <QMainWindow>
#include "ui_PowerWindow.h"
#include "../DCC-EX/DccEx.h"

class DccEx;

class PowerWindow : public QMainWindow {
Q_OBJECT

public:
    explicit PowerWindow(QWidget *parent = nullptr, DccEx *dccExInstance = nullptr); // Add a pointer to a dccEx window
    ~PowerWindow() override;
    static void connectButton(QPushButton* button, const QString& command, DccEx* dccExInstance);

private:
    Ui_PowerWindow *ui;


};

#endif // POWERWINDOW_H