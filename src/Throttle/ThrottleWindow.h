#ifndef THROTTLEWINDOW_H
#define THROTTLEWINDOW_H

#include <QMainWindow>
#include "ui_ThrottleWindow.h" // Include the UI header file

class ThrottleWindow : public QMainWindow {
Q_OBJECT

public:
    explicit ThrottleWindow(QWidget *parent = nullptr);

    ~ThrottleWindow() override;

    // Add your methods here

private:
    Ui::ThrottleWindow *ui; // Add this line
};

#endif // THROTTLEWINDOW_H