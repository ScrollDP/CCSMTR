#ifndef CCSMTR_INTELIBOX_I_H
#define CCSMTR_INTELIBOX_I_H

#include <QWidget>
#include "ui_intelibox_I.h"

class intelibox_I : public QWidget {
Q_OBJECT

public:
    explicit intelibox_I(QWidget *parent = nullptr);

private slots:
    void onConnectButtonClicked();
    void onDisconnectButtonClicked();
    void onInputReturnPressed();

private:
    Ui::intelibox_I ui;

};

#endif //CCSMTR_INTELIBOX_I_H