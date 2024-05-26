#include "dccEx.h"
#include <QSerialPortInfo>

dccEx::dccEx(QWidget *parent) : QWidget(parent) {
    ui.setupUi(this);

    // Populate the serial port combo box with available ports
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
        ui.serialPortComboBox->addItem(info.portName());

    // Connect the signals and slots
    connect(ui.connectButton, &QPushButton::clicked, this, &dccEx::onConnectButtonClicked);
    connect(ui.disconnectButton, &QPushButton::clicked, this, &dccEx::onDisconnectButtonClicked);
    connect(ui.consoleInput, &QLineEdit::returnPressed, this, &dccEx::onInputReturnPressed);
}

void dccEx::onConnectButtonClicked() {
    // Implement the connection logic
    ui.connectButton->setEnabled(false);
    ui.serialPortComboBox->setEnabled(false);
}

void dccEx::onDisconnectButtonClicked() {
    // Implement the disconnection logic
    ui.connectButton->setEnabled(true);
    ui.serialPortComboBox->setEnabled(true);
}

void dccEx::onInputReturnPressed() {
    // Implement the logic to send the input
}