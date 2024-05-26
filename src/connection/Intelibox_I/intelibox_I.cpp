#include "intelibox_I.h"
#include "../../mainWindow/mainWindow.h"
#include <QSerialPortInfo>
#include <QLineEdit>
#include <QMessageBox>
#include <QCloseEvent>

intelibox_I::intelibox_I(QWidget *parent) : QWidget(parent) {

    ui.setupUi(this);

    // Populate the serial port combo box with available ports
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
        ui.serialPortComboBox->addItem(info.portName());

    // Connect the signals and slots
    connect(ui.connectButton, &QPushButton::clicked, this, &intelibox_I::onConnectButtonClicked);
    connect(ui.disconnectButton, &QPushButton::clicked, this, &intelibox_I::onDisconnectButtonClicked);
    connect(ui.consoleInput, &QLineEdit::returnPressed, this, &intelibox_I::onInputReturnPressed);
}

void intelibox_I::onConnectButtonClicked() {
    if (!mainWindow::isAnyConnected) {
        // Implement the connection logic
        ui.connectButton->setEnabled(false);
        ui.serialPortComboBox->setEnabled(false);
        mainWindow::isAnyConnected = true;
        // Disable the "Connect" button of the other communication
    }
}

void intelibox_I::onDisconnectButtonClicked() {
    // Implement the disconnection logic
    ui.connectButton->setEnabled(true);
    ui.serialPortComboBox->setEnabled(true);
    mainWindow::isAnyConnected = false;
    // Enable the "Connect" button of the other communication
}

void intelibox_I::onInputReturnPressed() {
    // Implement the logic to send the input
}

