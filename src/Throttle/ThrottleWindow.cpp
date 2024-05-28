#include "ThrottleWindow.h"
#include <QIntValidator>

ThrottleWindow::ThrottleWindow(QWidget *parent, dccEx *dccExInstance) : QMainWindow(parent), ui(new Ui::ThrottleWindow) {
    ui->setupUi(this);
    ui->inputAdress->setValidator(new QIntValidator(this));
    ui->EmergencyStop->setStyleSheet("background-color: #8b0000");

    for (int i = 0; i <= 28; i++) {
        auto* button = this->findChild<QPushButton*>(QString("F%1").arg(i));
        if (button) {
            button->setEnabled(false);
            connect(button, &QPushButton::clicked, this, [=]() {
                onFunctionButtonClicked(dccExInstance);
            });
        }
    }

    setButtonsEnabled(false);
    connectButtons(dccExInstance);
}

void ThrottleWindow::setButtonsEnabled(bool enabled) {
    ui->speedSlider->setEnabled(enabled);
    ui->ReleaseButton->setEnabled(enabled);
    ui->ForwardSpeed->setEnabled(enabled);
    ui->ReverseSpeed->setEnabled(enabled);
    ui->EmergencyPause->setEnabled(enabled);
}

void ThrottleWindow::connectButtons(dccEx *dccExInstance) {
    connect(ui->AquireButton, &QPushButton::clicked, this, &ThrottleWindow::onAquireButtonClicked);
    connect(ui->ReleaseButton, &QPushButton::clicked, this, &ThrottleWindow::onReleaseButtonClicked);
    connect(ui->speedSlider, &QSlider::valueChanged, this, [=](int value) {
        onSpeedSliderValueChanged(value, dccExInstance);
    });
    connect(ui->ForwardSpeed, &QPushButton::clicked, this, [=](){
        onForwardButtonClicked(dccExInstance);
    });
    connect(ui->ReverseSpeed, &QPushButton::clicked, this, [=](){
        onReverseButtonClicked(dccExInstance);
    });
    connect(ui->EmergencyStop, &QPushButton::clicked, this, [=](){
        sendToArduino("<0>", dccExInstance);
        sendToArduino("<!>", dccExInstance);
        ui->speedSlider->setValue(0);
    });
    connect(ui->EmergencyPause, &QPushButton::clicked, this, [=](){
        QString command = QString("<t %1 %2 %3>").arg(ui->inputAdress->text()).arg(-1).arg(direction);
        //QString command = QString("<- " + ui->inputAdress->text() + ">");
        sendToArduino(command, dccExInstance);
        //ui->speedSlider->setValue(0);
    });
}

void ThrottleWindow::onAquireButtonClicked() {
    for (int i = 0; i <= 28; i++) {
        auto* button = this->findChild<QPushButton*>(QString("F%1").arg(i));
        if (button) {
            button->setEnabled(true);
        }
    }
    setButtonsEnabled(true);
    ui->inputAdress->setEnabled(false);
    ui->AquireButton->setEnabled(false);

}

void ThrottleWindow::onReleaseButtonClicked() {
    for (int i = 0; i <= 28; i++) {
        auto* button = this->findChild<QPushButton*>(QString("F%1").arg(i));
        if (button) {
            button->setEnabled(false);
        }
    }
    setButtonsEnabled(false);
    ui->inputAdress->setEnabled(true);
    ui->AquireButton->setEnabled(true);
}

void ThrottleWindow::onSpeedSliderValueChanged(int value,dccEx *dccExInstance) {
    QString command = QString("<t %1 %2 %3>").arg(ui->inputAdress->text()).arg(value).arg(direction);
    sendToArduino(command, dccExInstance);
}

void ThrottleWindow::onForwardButtonClicked(dccEx *dccExInstance) {
    setDirection(1, dccExInstance);
    ui->ReverseSpeed->setEnabled(true);
    ui->ForwardSpeed->setEnabled(false);
}

void ThrottleWindow::onReverseButtonClicked(dccEx *dccExInstance) {
    setDirection(0, dccExInstance);
    ui->ForwardSpeed->setEnabled(true);
    ui->ReverseSpeed->setEnabled(false);
}

void ThrottleWindow::setDirection(int dir, dccEx *dccExInstance) {
    direction = dir;
    ui->ReverseSpeed->setEnabled(!dir);
    ui->ForwardSpeed->setEnabled(dir);
    ui->speedSlider->setValue(0);
    QString command = QString("<t %1 %2 %3>").arg(ui->inputAdress->text()).arg(FRspeed).arg(direction);
    sendToArduino(command, dccExInstance);
}

void ThrottleWindow::onFunctionButtonClicked(dccEx *dccExInstance) {
    auto* button = qobject_cast<QPushButton*>(sender());
    if (!button) {
        return;
    }

    QString name = button->objectName();
    int number = name.mid(1).toInt();

    int newState = (functionButtonStates[name] + 1) % 2;
    functionButtonStates[name] = newState;

    button->setStyleSheet(newState ? "background-color: #FFA500; border: 2px solid #FFA500;" : "");

    QString command = QString("<F %1 %2 %3>").arg(ui->inputAdress->text()).arg(number).arg(newState);
    sendToArduino(command, dccExInstance);
}

void ThrottleWindow::sendToArduino(const QString &dataList, dccEx *dccExInstance) {
    dccExInstance->sendCommand(dataList);
}

ThrottleWindow::~ThrottleWindow() {
    delete ui;
}