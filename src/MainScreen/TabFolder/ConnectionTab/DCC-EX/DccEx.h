#ifndef CCSMTR_DCCEX_H
#define CCSMTR_DCCEX_H

#include <QWidget>
#include <QSerialPort>
#include "ui_DccEx.h"
#include "../../../MainWindow/MainWindow.h"


class DccEx : public QWidget {
Q_OBJECT



public:
    explicit DccEx(QWidget *parent = nullptr);
    ~DccEx() override;

    std::unique_ptr<QSerialPort> arduino;


    void sendCommand(const QString &dataList); // Add a method to send the command


private slots:
    void onConnectButtonClicked();
    void onDisconnectButtonClicked();
    void onInputReturnPressed();
    void onDataReceived();


private:
    Ui_DccEx ui{};

    void setupArduino();

    [[maybe_unused]] bool eventFilter(QObject *obj, QEvent *event) override;

};

#endif //CCSMTR_DCCEX_H