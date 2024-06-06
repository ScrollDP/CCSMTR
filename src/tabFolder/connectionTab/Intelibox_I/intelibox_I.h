#ifndef CCSMTR_INTELIBOX_I_H
#define CCSMTR_INTELIBOX_I_H

#include <QWidget>
#include <QSerialPort>
#include "ui_intelibox_I.h"
#include <boost/asio.hpp>

using namespace boost::asio;
using namespace std;

class intelibox_I : public QWidget {
Q_OBJECT

public:
    explicit intelibox_I(QWidget *parent = nullptr);
    ~intelibox_I() override;

    void setBaudRate(int baudRate);
    void setSyntax(const QString& syntax);

private slots:
    void onConnectButtonClicked();
    void onDisconnectButtonClicked();
    void onInputReturnPressed();
    void onDataReceived();

private:
    Ui::intelibox_I ui{};
    //QSerialPort *intelibox;
    int baudRate;
    QString syntax = "6050 and IB";
    io_service io;
    serial_port port{io};

    bool eventFilter(QObject *obj, QEvent *event);
};

#endif //CCSMTR_INTELIBOX_I_H
