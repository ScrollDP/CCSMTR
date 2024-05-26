#include "dccEx.h"
#include "../../mainWindow/mainWindow.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QCloseEvent>

dccEx::dccEx(QWidget *parent) : QWidget(parent) {
    ui.setupUi(this);

    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
        ui.serialPortComboBox->addItem(info.portName());

    connect(ui.connectButton, &QPushButton::clicked, this, &dccEx::onConnectButtonClicked);
    connect(ui.disconnectButton, &QPushButton::clicked, this, &dccEx::onDisconnectButtonClicked);
    connect(ui.consoleInput, &QLineEdit::returnPressed, this, &dccEx::onInputReturnPressed);
}

void dccEx::onConnectButtonClicked() {
    if (!mainWindow::isAnyConnected) {
        // Implement the connection logic
        ui.connectButton->setEnabled(false);
        ui.serialPortComboBox->setEnabled(false);
        mainWindow::isAnyConnected = true;
        // Disable the "Connect" button of the other communication
    }
}

void dccEx::onDisconnectButtonClicked() {
    // Implement the disconnection logic
    ui.connectButton->setEnabled(true);
    ui.serialPortComboBox->setEnabled(true);
    mainWindow::isAnyConnected = false;
    // Enable the "Connect" button of the other communication
}

void dccEx::onInputReturnPressed() {
    // Implement the logic to send the input
}

