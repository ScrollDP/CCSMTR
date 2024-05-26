#include "intelibox_I.h"
#include "../../mainWindow/mainWindow.h"
#include <QSerialPortInfo>
#include <QLineEdit>
#include <QMessageBox>
#include <QCloseEvent>

intelibox_I::intelibox_I(QWidget *parent) : QWidget(parent), intelibox(new QSerialPort(this)) {

    ui.setupUi(this);

    // Populate the serial port combo box with available ports
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
        ui.serialPortComboBox->addItem(info.portName());

    // Connect the signals and slots
    connect(ui.connectButton, &QPushButton::clicked, this, &intelibox_I::onConnectButtonClicked);
    connect(ui.disconnectButton, &QPushButton::clicked, this, &intelibox_I::onDisconnectButtonClicked);
    connect(ui.consoleInput, &QLineEdit::returnPressed, this, &intelibox_I::onInputReturnPressed);
    connect(intelibox, &QSerialPort::readyRead, this, &intelibox_I::onDataReceived); // Connect the readyRead signal to the onDataReceived slot
}

void intelibox_I::onConnectButtonClicked() {
    if (!mainWindow::isAnyConnected) {
        // Implement the connection logic
        intelibox->setPortName(ui.serialPortComboBox->currentText());
        intelibox->open(QIODevice::ReadWrite);
        intelibox->setBaudRate(QSerialPort::Baud115200);
        intelibox->setDataBits(QSerialPort::Data8);
        intelibox->setParity(QSerialPort::NoParity);
        intelibox->setStopBits(QSerialPort::OneStop);
        intelibox->setFlowControl(QSerialPort::NoFlowControl);

        ui.connectButton->setEnabled(false);
        ui.serialPortComboBox->setEnabled(false);
        mainWindow::isAnyConnected = true;
    }
}

void intelibox_I::onDisconnectButtonClicked() {
    // Implement the disconnection logic
    intelibox->close();
    ui.connectButton->setEnabled(true);
    ui.serialPortComboBox->setEnabled(true);
    mainWindow::isAnyConnected = false;
}

void intelibox_I::onInputReturnPressed() {
    // Implement the logic to send the input
}

void intelibox_I::onDataReceived() {
    // Read the data from the Intelibox
    QByteArray data = intelibox->readAll();
    // Convert the QByteArray to a QString
    QString text = QString::fromUtf8(data);
    // Append the text to the consoleOutput text edit
    ui.consoleOutput->append(text);
}