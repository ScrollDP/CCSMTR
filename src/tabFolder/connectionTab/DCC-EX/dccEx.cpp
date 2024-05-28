#include "dccEx.h"
#include "../../../mainWindow/mainWindow.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QKeyEvent>

dccEx::dccEx(QWidget *parent) : QWidget(parent){
    ui.setupUi(this);

    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts())
        ui.serialPortComboBox->addItem(info.portName());

    connect(ui.connectButton, &QPushButton::clicked, this, &dccEx::onConnectButtonClicked);
    connect(ui.disconnectButton, &QPushButton::clicked, this, &dccEx::onDisconnectButtonClicked);
    connect(ui.consoleInput, &QLineEdit::returnPressed, this, &dccEx::onInputReturnPressed);
    ui.consoleInput->installEventFilter(this);
}



  /*  if (mainWindow::isAnyConnected) {
        for (const QString &data : dataList) {
            arduino.write(data.toUtf8());
            qDebug()<< data;
            ui.consoleOutput->append(data);
        }
    }*/


void dccEx::onConnectButtonClicked() {

      if (!arduino.isOpen() && mainWindow::isAnyConnected){
          QMessageBox::critical(this, "Error", "Port už je otvoreny!");
      }
         else {
        ui.connectButton->setEnabled(false);
        ui.serialPortComboBox->setEnabled(false);
        mainWindow::isAnyConnected = true;
        arduino.setPortName(ui.serialPortComboBox->currentText());
        arduino.open(QIODevice::ReadWrite);
        arduino.setBaudRate(QSerialPort::Baud115200);
        arduino.setDataBits(QSerialPort::Data8);
        arduino.setParity(QSerialPort::NoParity);
        arduino.setStopBits(QSerialPort::OneStop);
        arduino.setFlowControl(QSerialPort::NoFlowControl);
        //qDebug()<< "Connect button clicked: Arduino open status = " << arduino.isOpen();
        connect(&arduino, &QSerialPort::readyRead, this, &dccEx::onDataReceived);
    }
}

void dccEx::onDisconnectButtonClicked() {
    if (!arduino.isOpen() && mainWindow::isAnyConnected){
        QMessageBox::warning(this, "Info", "Najprv odpojte predchádzajúce pripojenie!");
    }
    else {
        //qDebug() << "Disconnect button clicked: Arduino open status before close = " << arduino.isOpen();
        arduino.close();
        //qDebug() << "Disconnect button clicked: Arduino open status after close = " << arduino.isOpen();
        ui.connectButton->setEnabled(true);
        ui.serialPortComboBox->setEnabled(true);
        mainWindow::isAnyConnected = false;
    }
}

void dccEx::onInputReturnPressed() {
    QString dataToSend = "<" + ui.consoleInput->text().trimmed() + ">";
    if (!dataToSend.isEmpty() && mainWindow::isAnyConnected) {
        arduino.write(dataToSend.toUtf8());
        ui.consoleOutput->append(dataToSend);
        ui.consoleInput->clear();
    }
}

void dccEx::onDataReceived() {
    ui.consoleOutput->append(arduino.readAll());
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

void dccEx::sendCommand(const QString &dataList) {
    if (!&arduino || !ui.consoleOutput) {
        //qWarning() << "Arduino or console output not initialized";
        return;
    }

    std::string str = dataList.toStdString();
    QByteArray byteArray = dataList.toUtf8();
    const char* cstr = byteArray.constData();
    qDebug() << "Data to send: " << cstr;

    if (arduino.isOpen()) {
        //qDebug() << "Before write: Arduino open status = " << arduino.isOpen();

        qint64 bytesWritten = arduino.write(cstr);
        if (bytesWritten == -1) {
            //qWarning() << "Error writing data to serial port:" << arduino.errorString();
        } else {
            //qWarning() << "Bytes written to serial port:" << bytesWritten;
        }
        ui.consoleOutput->append(cstr);
        //qDebug() << "After write: Arduino open status = " << arduino.isOpen();
    } else {
        //qWarning() << "Failed to write to Arduino: device not open or not connected";
    }
}

dccEx::~dccEx() {
    mainWindow::isAnyConnected = false;
    delete &arduino;

}