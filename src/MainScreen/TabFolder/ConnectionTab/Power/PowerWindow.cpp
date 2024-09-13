#include "PowerWindow.h"

PowerWindow::PowerWindow(QWidget *parent, dccEx *dccExInstance) : QMainWindow(parent), ui(new Ui::PowerWindow){
    ui->setupUi(this);

    connectButton(ui->PowerOn, "<1>", dccExInstance);
    connectButton(ui->PowerOff, "<0>", dccExInstance);
    connectButton(ui->PowerOnMain, "<1 MAIN>", dccExInstance);
    connectButton(ui->PowerOffMain, "<0 MAIN>", dccExInstance);
    connectButton(ui->PowerOnProg, "<1 PROG>", dccExInstance);
    connectButton(ui->PowerOffProg, "<0 PROG>", dccExInstance);
    connectButton(ui->PowerOnJoin, "<1 JOIN>", dccExInstance);
}

void PowerWindow::connectButton(QPushButton* button, const QString& command, dccEx* dccExInstance) {
    connect(button, &QPushButton::clicked, [=]() {
        dccExInstance->sendCommand(command);
    });
}

PowerWindow::~PowerWindow() {
    delete ui;
}