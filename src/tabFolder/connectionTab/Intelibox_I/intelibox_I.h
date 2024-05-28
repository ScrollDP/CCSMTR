#ifndef CCSMTR_INTELIBOX_I_H
#define CCSMTR_INTELIBOX_I_H

#include <QWidget>
#include <QSerialPort> // Include the QSerialPort header
#include "ui_intelibox_I.h"

class intelibox_I : public QWidget {
Q_OBJECT

public:
    explicit intelibox_I(QWidget *parent = nullptr);

    ~intelibox_I() override;

private slots:
    void onConnectButtonClicked();
    void onDisconnectButtonClicked();
    void onInputReturnPressed();
    void onDataReceived(); // Add a slot for when data is received

private:
    Ui::intelibox_I ui{};
    QSerialPort *intelibox; // Add a QSerialPort member

};

#endif //CCSMTR_INTELIBOX_I_H