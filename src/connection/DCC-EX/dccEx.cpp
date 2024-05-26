#include "dccEx.h"
#include "../../mainWindow/mainWindow.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QKeyEvent>

dccEx::dccEx(QWidget *parent) : QWidget(parent), arduino(new QSerialPort(this)) {
    ui.setupUi(this);
    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts())
        ui.serialPortComboBox->addItem(info.portName());

    connect(ui.connectButton, &QPushButton::clicked, this, &dccEx::onConnectButtonClicked);
    connect(ui.disconnectButton, &QPushButton::clicked, this, &dccEx::onDisconnectButtonClicked);
    connect(ui.consoleInput, &QLineEdit::returnPressed, this, &dccEx::onInputReturnPressed);
    ui.consoleInput->installEventFilter(this);
}

void dccEx::onConnectButtonClicked() {
    if (!mainWindow::isAnyConnected && setupArduino()) {
        ui.connectButton->setEnabled(false);
        ui.serialPortComboBox->setEnabled(false);
        mainWindow::isAnyConnected = true;
        connect(arduino, &QSerialPort::readyRead, this, &dccEx::onDataReceived);
    }
}

void dccEx::onDisconnectButtonClicked() {
    arduino->close();
    ui.connectButton->setEnabled(true);
    ui.serialPortComboBox->setEnabled(true);
    mainWindow::isAnyConnected = false;
}

void dccEx::onInputReturnPressed() {
    QString dataToSend = "<" + ui.consoleInput->text().trimmed() + ">";
    if (!dataToSend.isEmpty() && mainWindow::isAnyConnected) {
        arduino->write(dataToSend.toUtf8());
        ui.consoleOutput->append(dataToSend);
        ui.consoleInput->clear();
    }
}

void dccEx::onDataReceived() {
    ui.consoleOutput->append(arduino->readAll());
}

bool dccEx::eventFilter(QObject *obj, QEvent *event) {
    if (obj == ui.consoleInput && event->type() == QEvent::KeyPress) {
        auto *keyEvent = dynamic_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
            onInputReturnPressed();
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}

bool dccEx::setupArduino() {
    arduino->setPortName(ui.serialPortComboBox->currentText());
    arduino->open(QIODevice::ReadWrite);
    arduino->setBaudRate(QSerialPort::Baud115200);
    arduino->setDataBits(QSerialPort::Data8);
    arduino->setParity(QSerialPort::NoParity);
    arduino->setStopBits(QSerialPort::OneStop);
    arduino->setFlowControl(QSerialPort::NoFlowControl);
    return arduino->isOpen() || QMessageBox::critical(this, "Error", "Failed to open the port!");
}