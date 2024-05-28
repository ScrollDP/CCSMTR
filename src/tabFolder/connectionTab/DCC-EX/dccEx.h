#ifndef CCSMTR_DCCEX_H
#define CCSMTR_DCCEX_H

#include <QWidget>
#include <QSerialPort>
#include "ui_dccEx.h"
#include <QThread>

class dccEx : public QWidget {
Q_OBJECT

public:
    explicit dccEx(QWidget *parent = nullptr);
    void sendCommand(const QString &dataList); // Add a method to send the command
    void onInputReturnPressed();

    ~dccEx() override;


private slots:
    void onConnectButtonClicked();
    void onDisconnectButtonClicked();


private:
    Ui::dccEx ui{};
    QSerialPort arduino{};



    void onDataReceived();

    bool eventFilter(QObject *obj, QEvent *event) override;

    bool setupArduino();
};

#endif //CCSMTR_DCCEX_H