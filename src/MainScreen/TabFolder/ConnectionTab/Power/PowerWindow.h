#ifndef POWERWINDOW_H
#define POWERWINDOW_H

#include <QMainWindow>
#include "ui_PowerWindow.h" // Include the UI header file
#include "../DCC-EX/DccEx.h"

class PowerWindow : public QMainWindow {
Q_OBJECT

public:
    explicit PowerWindow(QWidget *parent = nullptr, dccEx *dccExInstance = nullptr); // Add a pointer to a dccEx window
    ~PowerWindow() override;

private:
    Ui::PowerWindow *ui; // Add this line

    void connectButton(QPushButton* button, const QString& command, dccEx* dccExInstance);
};

#endif // POWERWINDOW_H