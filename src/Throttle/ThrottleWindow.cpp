#include "ThrottleWindow.h"
#include <QIntValidator>


ThrottleWindow::ThrottleWindow(QWidget *parent, dccEx *dccExInstance) : QMainWindow(parent), ui(new Ui::ThrottleWindow) {
    ui->setupUi(this);

    // Limit the inputAdress to only accept integer input
    auto* validator = new QIntValidator(this);
    ui->inputAdress->setValidator(validator);
    ui->EmergencyStop->setStyleSheet("background-color: #8b0000");


    // Connect signals and slots
    for (int i = 0; i <= 28; i++) {
        auto* button = this->findChild<QPushButton*>(QString("F%1").arg(i));
        if (button) {
            button->setEnabled(false);
            connect(button, &QPushButton::clicked, this, [=]() {
                ThrottleWindow::onFunctionButtonClicked(dccExInstance);
            });
        }
    }

    ui->speedSlider->setEnabled(false);
    ui->ReleaseButton->setEnabled(false);
    ui->ForwardSpeed->setEnabled(false);
    ui->ReverseSpeed->setEnabled(false);
    ui->EmergencyPause->setEnabled(false);

    // Connect signals and slots
    connect(ui->AquireButton, &QPushButton::clicked, this, &ThrottleWindow::onAquireButtonClicked);
    connect(ui->ReleaseButton, &QPushButton::clicked, this, &ThrottleWindow::onReleaseButtonClicked);
    connect(ui->speedSlider, &QSlider::valueChanged, this, [=](int value) {
        onSpeedSliderValueChanged(value, dccExInstance);

    });

    connect(ui->ForwardSpeed, &QPushButton::clicked, this, [=](){
        ThrottleWindow::onForwardButtonClicked(dccExInstance);
    });
    connect(ui->ReverseSpeed, &QPushButton::clicked, this, [=](){
        ThrottleWindow::onReverseButtonClicked(dccExInstance);
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
    ui->ForwardSpeed->setEnabled(true);
    ui->ReverseSpeed->setEnabled(true);
    ui->inputAdress->setEnabled(false);
    ui->AquireButton->setEnabled(false);
    ui->EmergencyPause->setEnabled(true);
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
    ui->EmergencyPause->setEnabled(false);
}

void ThrottleWindow::onSpeedSliderValueChanged(int value,dccEx *dccExInstance) {
    // When the value of the speedSlider changes, send the command to the Arduino

    QString command = QString("<t %1 %2 %3>").arg(ui->inputAdress->text()).arg(value).arg(direction);
    //qDebug() << "Command sent SpeedSlider: " << command;
    ThrottleWindow::sendToArduino(command, dccExInstance);
}

void ThrottleWindow::onForwardButtonClicked(dccEx *dccExInstance) {
    direction = 1;
    ui->ReverseSpeed->setEnabled(true);
    ui->ForwardSpeed->setEnabled(false);
    ui->speedSlider->setValue(0);
    QString command = QString("<t %1 %2 %3>").arg(ui->inputAdress->text()).arg(FRspeed).arg(direction);
    ThrottleWindow::sendToArduino(command, dccExInstance);
}
void ThrottleWindow::onReverseButtonClicked(dccEx *dccExInstance) {
    direction = 0;
    ui->ForwardSpeed->setEnabled(true);
    ui->ReverseSpeed->setEnabled(false);
    ui->speedSlider->setValue(0);
    QString command = QString("<t %1 %2 %3>").arg(ui->inputAdress->text()).arg(FRspeed).arg(direction);
    ThrottleWindow::sendToArduino(command, dccExInstance);
}


void ThrottleWindow::onFunctionButtonClicked(dccEx *dccExInstance) {
    // Get the button that was clicked
    auto* button = qobject_cast<QPushButton*>(sender());
    if (!button) {
        return;
    }

    // Extract the number from the button's name
    QString name = button->objectName();
    int number = name.mid(1).toInt();  // Remove the 'F' and convert the rest to an integer

    // Toggle the state of the button
    int newState = (functionButtonStates[name] + 1) % 2;
    functionButtonStates[name] = newState;

    // Change the color of the button
    if (newState == 1) {
        button->setStyleSheet("background-color: #FFA500; border: 2px solid #FFA500;");
    } else {
        button->setStyleSheet("");
    }

    // Send the command to the Arduino
    QString command = QString("<F %1 %2 %3>").arg(ui->inputAdress->text()).arg(number).arg(newState);
    ThrottleWindow::sendToArduino(command, dccExInstance);
}

void ThrottleWindow::sendToArduino(const QString &dataList, dccEx *dccExInstance) {
    // Send the command to the Arduino
    //qDebug() << "Command sent: " << command;
    dccExInstance->sendCommand(dataList);
}

ThrottleWindow::~ThrottleWindow() {
    delete ui;
}

