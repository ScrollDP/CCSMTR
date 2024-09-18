#include "DccEx.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QKeyEvent>

QQueue<QString> commandQueue;

DccEx::DccEx(QWidget *parent)
        : QWidget(parent),
        arduino(new QSerialPort(this)) {
        ui.setupUi(this);

    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts())
        ui.serialPortComboBox->addItem(info.portName());

    connect(ui.connectButton, &QPushButton::clicked, this, &DccEx::onConnectButtonClicked);
    connect(ui.disconnectButton, &QPushButton::clicked, this, &DccEx::onDisconnectButtonClicked);
    connect(ui.consoleInput, &QLineEdit::returnPressed, this, &DccEx::onInputReturnPressed);
    ui.consoleInput->installEventFilter(this);

    // Timer to check the queue
    auto *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DccEx::readFromQueue);
    timer->start(500); // Check every second
}

void DccEx::onConnectButtonClicked() {

      if (!arduino->isOpen() && MainWindow::isAnyConnected){
          QMessageBox::critical(this, "Error", "Port už je otvoreny!");
      } else {
          setupArduino();
          //qDebug()<< "Connect button clicked: Arduino open status = " << arduino->isOpen();
          connect(arduino.get(), &QSerialPort::readyRead, this, &DccEx::onDataReceived);
    }
}

void DccEx::setupArduino() const {
    ui.connectButton->setEnabled(false);
    ui.serialPortComboBox->setEnabled(false);
    MainWindow::isAnyConnected = true;
    arduino->setPortName(ui.serialPortComboBox->currentText());
    arduino->open(QIODevice::ReadWrite);
    arduino->setBaudRate(QSerialPort::Baud115200);
    arduino->setDataBits(QSerialPort::Data8);
    arduino->setParity(QSerialPort::NoParity);
    arduino->setStopBits(QSerialPort::OneStop);
    arduino->setFlowControl(QSerialPort::NoFlowControl);
}

void DccEx::onDisconnectButtonClicked() {
    if (!arduino->isOpen() && MainWindow::isAnyConnected){
        QMessageBox::warning(this, "Info", "Najprv odpojte predchádzajúce pripojenie!");
    }
    else {
        //qDebug() << "Disconnect button clicked: Arduino open status before close = " << arduino->isOpen();
        arduino->close();
        //qDebug() << "Disconnect button clicked: Arduino open status after close = " << arduino->isOpen();
        ui.connectButton->setEnabled(true);
        ui.serialPortComboBox->setEnabled(true);
        MainWindow::isAnyConnected = false;
    }
}

void DccEx::onInputReturnPressed() const {
    QString dataToSend = "<" + ui.consoleInput->text().trimmed() + ">";
    if (!dataToSend.isEmpty() && MainWindow::isAnyConnected) {
        arduino->write(dataToSend.toUtf8());
        ui.consoleOutput->append(dataToSend);
        ui.consoleInput->clear();
    }
}

void DccEx::onDataReceived() const {
    ui.consoleOutput->append(arduino->readAll());
}

[[maybe_unused]] bool DccEx::eventFilter(QObject *obj, QEvent *event) {
    if (obj == ui.consoleInput && event->type() == QEvent::KeyPress) {
        auto *keyEvent = dynamic_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
            onInputReturnPressed();
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}

void DccEx::sendCommand(const QString &dataList) const {
    if (!arduino || !ui.consoleOutput) {
        //qWarning() << "Arduino or console output not initialized";
        return;
    }

    if (arduino->isOpen()) {
        arduino->write(dataList.toUtf8());
        ui.consoleOutput->append(dataList);
        qDebug()<< "Data sent to Arduino: " << dataList;
        //qDebug() << "After write: Arduino open status = " << arduino->isOpen();
    } else {
        //qWarning() << "Failed to write to Arduino: device not open or not connected";
    }
}

void DccEx::readFromQueue() const {
    while (!commandQueue.isEmpty()) {
        QString command = commandQueue.dequeue();
        if (!command.isEmpty()) {
            sendCommand(command);
        }
    }
}

DccEx::~DccEx() {
    MainWindow::isAnyConnected = false;
}