#include "mainWindow.h"
#include <QCloseEvent>

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
    dccExWindow = new dccEx(nullptr);
    intelibox_IWindow = new intelibox_I(nullptr);

    connect(ui.actionDCC_EX, &QAction::triggered, this, &mainWindow::onActionDCC_EXTriggered);
    connect(ui.actionIntelibox_I, &QAction::triggered, this, &mainWindow::onActionIntelibox_ITriggered);
}

mainWindow::~mainWindow() {
    delete dccExWindow; // Delete the dccEx window
    delete intelibox_IWindow; // Delete the Intelibox_I window
}

void mainWindow::onActionDCC_EXTriggered() {
    dccExWindow->show();
}

void mainWindow::onActionIntelibox_ITriggered() {
    intelibox_IWindow->show();
}

void mainWindow::closeEvent(QCloseEvent *event) {
    dccExWindow->close();
    intelibox_IWindow->close();
    event->accept();
}
bool mainWindow::isAnyConnected = false; // Add this line
