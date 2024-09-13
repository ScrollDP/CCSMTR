#ifndef CCSMTR_DCCEX_H
#define CCSMTR_DCCEX_H

#include <QWidget>
#include <QSerialPort>
#include "ui_DccEx.h"
#include "../../../MainWindow/MainWindow.h"

class dccEx : public QWidget {
Q_OBJECT

public:
    explicit dccEx(QWidget *parent = nullptr);
    ~dccEx() override;


    void sendCommand(const QString &dataList); // Add a method to send the command


private slots:
    void onConnectButtonClicked();
    void onDisconnectButtonClicked();
    void onInputReturnPressed();
    void onDataReceived();


private:
    Ui::dccEx ui;
    std::unique_ptr<QSerialPort> arduino;
    void setupArduino();

    bool eventFilter(QObject *obj, QEvent *event) override;

};

#endif //CCSMTR_DCCEX_H