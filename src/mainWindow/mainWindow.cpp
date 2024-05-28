#include "mainWindow.h"
#include <QCloseEvent>

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
    dccExWindow = new dccEx(nullptr);
    intelibox_IWindow = new intelibox_I(nullptr);
    powerWindow = new PowerWindow(nullptr, dccExWindow);

    connect(ui.actionDCC_EX, &QPushButton::clicked, this, &mainWindow::onActionDCC_EXTriggered);
    connect(ui.actionIntelibox_I, &QPushButton::clicked, this, &mainWindow::onActionIntelibox_ITriggered);
    connect(ui.actionThrottle, &QPushButton::clicked, this, &mainWindow::onActionThrottleTriggered);
    connect(ui.actionPower, &QPushButton::clicked, this, &mainWindow::onActionPowerTriggered);
}

bool mainWindow::isAnyConnected = false;

mainWindow::~mainWindow() {
    delete dccExWindow; // Delete the dccEx window
    delete intelibox_IWindow; // Delete the Intelibox_I window
    delete powerWindow; // Delete the PowerWindow window
}

void mainWindow::onActionDCC_EXTriggered() {
    dccExWindow->show();
}

void mainWindow::onActionIntelibox_ITriggered() {
    intelibox_IWindow->show();
}
void mainWindow::onActionPowerTriggered() {
    powerWindow->show();
}

void mainWindow::closeEvent(QCloseEvent *event) {
    dccExWindow->close();
    intelibox_IWindow->close();
    powerWindow->close();
    event->accept();
}

void mainWindow::onActionThrottleTriggered() {
    auto *throttleWindow = new ThrottleWindow(this,dccExWindow);
    throttleWindow->setAttribute(Qt::WA_DeleteOnClose);
    throttleWindow->show();
}
