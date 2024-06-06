#include "intelibox_I.h"
#include "../../../mainWindow/mainWindow.h"
#include <QSerialPortInfo>
#include <QLineEdit>
#include <QMessageBox>
#include <QCloseEvent>
#include <charconv>
#include <array>

intelibox_I::intelibox_I(QWidget *parent) : QWidget(parent), port(io) {
    ui.setupUi(this);

    ui.consoleInput->installEventFilter(this);

    baudRate = 2400;


    // Populate the serial port combo box with available ports
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
        ui.serialPortComboBox->addItem(info.portName());

    // Connect the signals and slots
    connect(ui.connectButton, &QPushButton::clicked, this, &intelibox_I::onConnectButtonClicked);
    connect(ui.disconnectButton, &QPushButton::clicked, this, &intelibox_I::onDisconnectButtonClicked);
    connect(ui.consoleInput, &QLineEdit::returnPressed, this, &intelibox_I::onInputReturnPressed);
}

void intelibox_I::setBaudRate(int newBaudRate) {
    baudRate = newBaudRate;
}

void intelibox_I::setSyntax(const QString& newSyntax) {
    syntax = newSyntax;
}

void intelibox_I::onConnectButtonClicked() {
    if (!port.is_open() && mainWindow::isAnyConnected){
        QMessageBox::critical(this, "Error", "Port už je otvoreny!");
    }
    else{
        // Implement the connectionTab logic

        try {
            port.open(ui.serialPortComboBox->currentText().toStdString());
            port.set_option(serial_port::baud_rate(baudRate));
        } catch (const boost::system::system_error& e) {
            QMessageBox::critical(this, "Error", "Failed to open port: " + QString::fromStdString(e.what()));
            return;
        }

        std::array<char, 128> data{};
        std::size_t size = data.size();


        setSyntax(syntax);
        boost::asio::async_read(port, boost::asio::buffer(data, size),
                                [this](boost::system::error_code ec, std::size_t length) {
                                    if (!ec) {
                                        // Read operation completed successfully.
                                        // Call the onDataReceived method.
                                        onDataReceived();
                                    }
                                });


        /*
        boost::asio::async_read(port, boost::asio::buffer(data, size),
        [this](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                // Read operation completed successfully.
                // Call the onDataReceived method.
                onDataReceived();
            }
        });*/

        ui.connectButton->setEnabled(false);
        ui.serialPortComboBox->setEnabled(false);
        mainWindow::isAnyConnected = true;
    }
}

void intelibox_I::onDisconnectButtonClicked() {
    if (!port.is_open() && mainWindow::isAnyConnected){
        QMessageBox::warning(this, "Info", "Najprv odpojte predchádzajúce pripojenie!");
    }
    else {
        // Implement the disconnection logic
        port.close();
        ui.connectButton->setEnabled(true);
        ui.serialPortComboBox->setEnabled(true);
        mainWindow::isAnyConnected = false;

    }
}

void intelibox_I::onInputReturnPressed() {
    // Get the text from the consoleInput QLineEdit
    QString input = ui.consoleInput->text();

    // Check if the input is not empty
    if (!input.isEmpty()) {
        // Convert the QString to a std::string
        std::string dataToSend = input.toStdString();

        // Write the data to the port
        boost::asio::write(port, boost::asio::buffer(dataToSend));

        // Clear the consoleInput QLineEdit
        ui.consoleInput->clear();
    }
}

bool intelibox_I::eventFilter(QObject *obj, QEvent *event) {
    if (obj == ui.consoleInput && event->type() == QEvent::KeyPress) {
        auto *keyEvent = dynamic_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
            onInputReturnPressed();
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}

void intelibox_I::onDataReceived() {
    // Read the data from the Intelibox
    boost::asio::streambuf buffer;
    boost::asio::read_until(port, buffer, '\n');

    // Convert the data to a QString
    std::istream is(&buffer);
    std::string s;
    std::getline(is, s);
    QString data = QString::fromStdString(s);

    // Display the data in the UI
    ui.consoleOutput->setText(data);
}

intelibox_I::~intelibox_I() {
    mainWindow::isAnyConnected = false;
}