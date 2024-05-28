#include "intelibox_I.h"
#include "../../../mainWindow/mainWindow.h"
#include <QSerialPortInfo>
#include <QLineEdit>
#include <QMessageBox>
#include <QCloseEvent>
#include <vector>
#include <string>


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
    if (!intelibox->isOpen() && mainWindow::isAnyConnected){
        QMessageBox::critical(this, "Error", "Port už je otvoreny!");
    }
    else{
        // Implement the connectionTab logic
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
    if (!intelibox->isOpen() && mainWindow::isAnyConnected){
        QMessageBox::warning(this, "Info", "Najprv odpojte predchádzajúce pripojenie!");
    }
    else {
        // Implement the disconnection logic
        intelibox->close();
        ui.connectButton->setEnabled(true);
        ui.serialPortComboBox->setEnabled(true);
        mainWindow::isAnyConnected = false;
    }
}

void intelibox_I::onInputReturnPressed() {
    // Implement the logic to send the input
}

std::string hexToStringVerbose(const std::string& hex) {
    std::string result;

    for (size_t i = 0; i < hex.length(); i += 2) {
        // Get the current pair of characters
        std::string byteString = hex.substr(i, 2);

        // Convert the pair of characters from hexadecimal to decimal
        char byte = static_cast<char>(std::stoi(byteString, nullptr, 16));

        // Append the character to the result string
        result += byte;
    }

    return result;
}

std::string hexToUtf8(const std::string& hex) {
    std::vector<unsigned char> bytes;

    for (unsigned int i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        auto byte = (unsigned char) strtol(byteString.c_str(), nullptr, 16);
        bytes.push_back(byte);
    }

    return std::string(bytes.begin(), bytes.end());
}

void intelibox_I::onDataReceived() {
    // Read the data from the Intelibox
    QByteArray data = intelibox->readAll();
    // Convert each byte to its hexadecimal representation
    QString hexData = data.toHex(' ').toUpper();
    // Convert the hexadecimal data to a UTF-8 string

    std::string utf8Data = hexToUtf8(hexData.toStdString());
    // Convert the UTF-8 string to a QString and append it to the consoleOutput text edit
    ui.consoleOutput->append(QString::fromStdString(utf8Data));

    //backup:
    //std::string verboseData = hexToStringVerbose(hexData.toStdString());
    //ui.consoleOutput->append(QString::fromStdString(verboseData));
}

intelibox_I::~intelibox_I() {
    mainWindow::isAnyConnected = false;
    delete intelibox;

}

