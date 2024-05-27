#include "ThrottleWindow.h"

ThrottleWindow::ThrottleWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::ThrottleWindow) {
    ui->setupUi(this);
    // Connect signals and slots here
}

ThrottleWindow::~ThrottleWindow() {
    delete ui;
}