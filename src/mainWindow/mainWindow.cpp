#include "mainWindow.h"
#include <QCloseEvent>

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent) {
    // ...
    hideTimer = new QTimer(this);
    hideTimer->setInterval(5000); // Set the interval
    connect(hideTimer, &QTimer::timeout, [this]() {
        ui.tabWidget->setVisible(false);
    });
    // ...

    ui.setupUi(this);
    //loading stationControll class to automatically load the ui
    stationControllWindow = new stationControll(this);
    ui.verticalLayout_3->addWidget(stationControllWindow);

    // Remove the tabWidget from the layout
    ui.verticalLayout_3->removeWidget(ui.tabWidget);

    // Make the tabWidget a child of the mainWindow but not part of the layout
    ui.tabWidget->setParent(this);
    ui.tabWidget->move(0, 0); // Position the tabWidget at the top-left corner

    ui.tabWidget->installEventFilter(this);
    this->installEventFilter(this);
    ui.tabWidget->setVisible(false);


    dccExWindow = new dccEx(nullptr);
    intelibox_IWindow = new intelibox_I(nullptr);
    powerWindow = new PowerWindow(nullptr, dccExWindow);


    connect(ui.actionDCC_EX, &QPushButton::clicked, this, &mainWindow::onActionDCC_EXTriggered);
    connect(ui.actionIntelibox_I, &QPushButton::clicked, this, &mainWindow::onActionIntelibox_ITriggered);
    connect(ui.actionThrottle, &QPushButton::clicked, this, &mainWindow::onActionThrottleTriggered);
    connect(ui.actionPower, &QPushButton::clicked, this, &mainWindow::onActionPowerTriggered);
    this->showFullScreen();
}

bool mainWindow::isAnyConnected = false;

mainWindow::~mainWindow() {
    delete dccExWindow; // Delete the dccEx window
    delete intelibox_IWindow; // Delete the Intelibox_I window
    delete powerWindow; // Delete the PowerWindow window
}

void mainWindow::onActionDCC_EXTriggered() {
    dccExWindow->show();
}

void mainWindow::onActionIntelibox_ITriggered() {
    intelibox_IWindow->show();
}
void mainWindow::onActionPowerTriggered() {
    powerWindow->show();
}

void mainWindow::closeEvent(QCloseEvent *event) {
    dccExWindow->close();
    intelibox_IWindow->close();
    powerWindow->close();
    event->accept();
}


void mainWindow::onActionThrottleTriggered() {
    auto *throttleWindow = new ThrottleWindow(this,dccExWindow);
    throttleWindow->setAttribute(Qt::WA_DeleteOnClose);
    throttleWindow->show();
}

void mainWindow::toggleFullScreen() {
    if (this->isFullScreen()) {
        this->showNormal();
    } else {
        this->showFullScreen();
    }
}

void mainWindow::toggleTabShow() {
    //condition on if tab is shown or not
    if (ui.tabWidget->isVisible()) {
        ui.tabWidget->setVisible(false);
    } else {
        ui.tabWidget->setVisible(true);
    }
}

void mainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_F11) {
        toggleFullScreen();
    } else {
        QMainWindow::keyPressEvent(event);
    }
    if (event->key() == Qt::Key_F10) {
        toggleTabShow();
    } else {
        QMainWindow::keyPressEvent(event);
    }
    if (event->key() == Qt::Key_F9) {
        ui.checkBox->setChecked(!ui.checkBox->isChecked());
        qDebug() << "F9 pressed";
        if(ui.checkBox->isChecked()){
            editMode(true);
            qDebug() << "editMode F9 is true";
        } else {
            editMode(false);
            qDebug() << "editMode F9 is false";
        }
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

bool mainWindow::eventFilter(QObject *watched, QEvent *event) {
    if (watched == this && event->type() == QEvent::HoverMove) {
        auto *mouseEvent = dynamic_cast<QHoverEvent*>(event);
        if (mouseEvent->position().y() <= 5) { // Check if the mouse is within 10px from the top
            ui.tabWidget->setVisible(true);
            hideTimer->start();
            //qDebug() << "Tab widget shown";
        }
        return true;
    } else if (watched == ui.tabWidget && event->type() == QEvent::Leave) {
        ui.tabWidget->setVisible(false);
        hideTimer->stop();
        //qDebug() << "Tab widget hidden LEAVE";
        return true;
    }
    return QMainWindow::eventFilter(watched, event);
}

bool mainWindow::editMode(bool mode) {
    if(mode){
        return true;
        qDebug() << "editMode is true";
    }
    else{
        return false;
        qDebug() << "editMode is false";
    }
}