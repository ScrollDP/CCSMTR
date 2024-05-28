#include "ThrottleWindow.h"
#include <QIntValidator>


ThrottleWindow::ThrottleWindow(QWidget *parent, dccEx *dccExInstance) : QMainWindow(parent), ui(new Ui::ThrottleWindow) {
    ui->setupUi(this);


    // Limit the inputAdress to only accept integer input
    auto* validator = new QIntValidator(this);
    ui->inputAdress->setValidator(validator);

    // Initially, disable all the function buttons, the speedSlider, and the ReleaseButton
    for (int i = 0; i <= 28; i++) {
        auto* button = this->findChild<QPushButton*>(QString("F%1").arg(i));
        if (button) {
            button->setEnabled(false);
        }
    }
    ui->speedSlider->setEnabled(false);
    ui->ReleaseButton->setEnabled(false);

    // Connect signals and slots
    connect(ui->AquireButton, &QPushButton::clicked, this, &ThrottleWindow::onAquireButtonClicked);
    connect(ui->ReleaseButton, &QPushButton::clicked, this, &ThrottleWindow::onReleaseButtonClicked);
    connect(ui->speedSlider, &QSlider::valueChanged, this, [=](int value) {
        onSpeedSliderValueChanged(value, dccExInstance);

    });


}

void ThrottleWindow::onAquireButtonClicked() {
    // When the AquireButton is clicked, enable all the function buttons, the speedSlider, and the ReleaseButton, and disable the inputAdress and the AquireButton
    for (int i = 0; i <= 28; i++) {
        auto* button = this->findChild<QPushButton*>(QString("F%1").arg(i));
        if (button) {
            button->setEnabled(true);
        }
    }
    ui->speedSlider->setEnabled(true);
    ui->ReleaseButton->setEnabled(true);
    ui->inputAdress->setEnabled(false);
    ui->AquireButton->setEnabled(false);
}

void ThrottleWindow::onReleaseButtonClicked() {
    // When the ReleaseButton is clicked, disable all the function buttons, the speedSlider, and the ReleaseButton, and enable the inputAdress and the AquireButton
    for (int i = 0; i <= 28; i++) {
        auto* button = this->findChild<QPushButton*>(QString("F%1").arg(i));
        if (button) {
            button->setEnabled(false);
        }
    }
    ui->speedSlider->setEnabled(false);
    ui->ReleaseButton->setEnabled(false);
    ui->inputAdress->setEnabled(true);
    ui->AquireButton->setEnabled(true);
}

void ThrottleWindow::onSpeedSliderValueChanged(int value,dccEx *dccExInstance) {
    // When the value of the speedSlider changes, send the command to the Arduino
    //QString command = QString("<t %1 %2 1>").arg(ui->inputAdress->text()).arg(value);


    QString command = QString("<t %1 %2 1>").arg(ui->inputAdress->text()).arg(value);
    qDebug() << "Command sent SpeedSlider: " << command;

    dccExInstance->sendCommand(command);

}


ThrottleWindow::~ThrottleWindow() {
    delete ui;
}

