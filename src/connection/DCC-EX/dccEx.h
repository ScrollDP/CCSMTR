#ifndef CCSMTR_DCCEX_H
#define CCSMTR_DCCEX_H

#include <QWidget>
#include "ui_dccEx.h"

class dccEx : public QWidget {
Q_OBJECT

public:
    explicit dccEx(QWidget *parent = nullptr);

private slots:
    void onConnectButtonClicked();
    void onDisconnectButtonClicked();
    void onInputReturnPressed();

private:
    Ui::dccEx ui;
};

#endif //CCSMTR_DCCEX_H