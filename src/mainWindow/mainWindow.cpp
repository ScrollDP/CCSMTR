#include "mainWindow.h"
#include <QCloseEvent>

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
    dccExWindow = new dccEx(nullptr); // Change the parent to nullptr
    intelibox_IWindow = new intelibox_I(nullptr); // Initialize the Intelibox_I window

    // Connect the triggered signal of actionDCC_EX to the onActionDCC_EXTriggered slot
    connect(ui.actionDCC_EX, &QAction::triggered, this, &mainWindow::onActionDCC_EXTriggered);
    // Connect the triggered signal of actionIntelibox_I to the onActionIntelibox_ITriggered slot
    connect(ui.actionIntelibox_I, &QAction::triggered, this, &mainWindow::onActionIntelibox_ITriggered);
}

mainWindow::~mainWindow() {
    delete dccExWindow; // Delete the dccEx window
    delete intelibox_IWindow; // Delete the Intelibox_I window
}

void mainWindow::onActionDCC_EXTriggered() {
    dccExWindow->show(); // Show the dccEx window
}

void mainWindow::onActionIntelibox_ITriggered() {
    intelibox_IWindow->show(); // Show the Intelibox_I window
}

void mainWindow::closeEvent(QCloseEvent *event) {
    dccExWindow->close(); // Close the dccEx window
    intelibox_IWindow->close(); // Close the Intelibox_I window
    // Terminate any open serial connections
    event->accept();
}