#include "MainWindow.h"
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // ...
    hideTimer = new QTimer(this);
    hideTimer->setInterval(5000); // Set the interval
    connect(hideTimer, &QTimer::timeout, [this]() {
        ui.tabWidget->setVisible(false);
    });
    // ...

    ui.setupUi(this);
    //loading StationControl class to automatically load the ui
    stationControllWindow = new StationControl(this);
    ui.verticalLayout_3->addWidget(stationControllWindow);

    // Remove the tabWidget from the layout
    ui.verticalLayout_3->removeWidget(ui.tabWidget);

    // Make the tabWidget a child of the MainWindow but not part of the layout
    ui.tabWidget->setParent(this);
    ui.tabWidget->move(0, 0); // Position the tabWidget at the top-left corner

    ui.tabWidget->installEventFilter(this);
    this->installEventFilter(this);
    ui.tabWidget->setVisible(false);


    dccExWindow = new dccEx(nullptr);
    powerWindow = new PowerWindow(nullptr, dccExWindow);


    connect(ui.actionDCC_EX, &QPushButton::clicked, this, &MainWindow::onActionDCC_EXTriggered);
    connect(ui.actionThrottle, &QPushButton::clicked, this, &MainWindow::onActionThrottleTriggered);
    connect(ui.actionPower, &QPushButton::clicked, this, &MainWindow::onActionPowerTriggered);
    connect(ui.checkBox, &QCheckBox::stateChanged, this, &MainWindow::editMode);
    this->showFullScreen();
}

bool MainWindow::isAnyConnected = false;

MainWindow::~MainWindow() {
    delete dccExWindow; // Delete the dccEx window
    delete powerWindow; // Delete the PowerWindow window
}

void MainWindow::onActionDCC_EXTriggered() {
    dccExWindow->show();
}

void MainWindow::onActionPowerTriggered() {
    powerWindow->show();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    dccExWindow->close();
    powerWindow->close();
    event->accept();
}


void MainWindow::onActionThrottleTriggered() {
    auto *throttleWindow = new ThrottleWindow(this,dccExWindow);
    throttleWindow->setAttribute(Qt::WA_DeleteOnClose);
    throttleWindow->show();
}

void MainWindow::toggleFullScreen() {
    if (this->isFullScreen()) {
        this->showNormal();
    } else {
        this->showFullScreen();
    }
}

void MainWindow::toggleTabShow() {
    //condition on if tab is shown or not
    if (ui.tabWidget->isVisible()) {
        ui.tabWidget->setVisible(false);
    } else {
        ui.tabWidget->setVisible(true);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
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

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
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

bool MainWindow::editMode(bool mode) {
    qDebug() << "editMode called";
    if(mode){
        qDebug() << "editMode is true";
        return true;
    }
    else{
        qDebug() << "editMode is false";
        return false;
    }
}