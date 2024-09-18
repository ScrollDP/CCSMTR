#ifndef CCSMTR_DCCEX_H
#define CCSMTR_DCCEX_H

#include <QWidget>
#include <QSerialPort>
#include "ui_DccEx.h"
#include "../../../MainWindow/MainWindow.h"
#include "CommandQueue.h"


class DccEx : public QWidget {
Q_OBJECT



public:
    explicit DccEx(QWidget *parent = nullptr);
    ~DccEx() override;

    std::unique_ptr<QSerialPort> arduino;


    void sendCommand(const QString &dataList) const; // Add a method to send the command


private slots:
    void onConnectButtonClicked();
    void onDisconnectButtonClicked();
    void onInputReturnPressed() const;
    void onDataReceived() const;


private:
    Ui_DccEx ui{};

    void setupArduino() const;

    [[maybe_unused]] bool eventFilter(QObject *obj, QEvent *event) override;

    void readFromQueue() const;
};

#endif //CCSMTR_DCCEX_H