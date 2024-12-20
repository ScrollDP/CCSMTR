#include "MainWindow.h"



MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent),
          ui(new Ui::MainWindow),
          stationControllWindow(new StationControl(this)) {

    ui->setupUi(this);

    //loading StationControl class to automatically load the ui
    ui->verticalLayout_3->addWidget(stationControllWindow);

    // Remove the tabWidget from the layout
    ui->verticalLayout_3->removeWidget(ui->tabWidget);

    // Make the tabWidget a child of the MainWindow but not part of the layout
    ui->tabWidget->setParent(this);
    ui->tabWidget->move(0, 0); // Position the tabWidget in the top-left corner

    ui->tabWidget->installEventFilter(this);
    this->installEventFilter(this);
    ui->tabWidget->setVisible(false);


    dccExWindow = new DccEx(nullptr);
    powerWindow = new PowerWindow(nullptr, dccExWindow);

    ui->PowerOnTrack->setStyleSheet("background-color: green");
    ui->PowerOffTrack->setStyleSheet("background-color: #8b0000");

    connect(ui->actionDCC_EX, &QPushButton::clicked, this, &MainWindow::onActionDCC_EXTriggered);
    connect(ui->actionThrottle, &QPushButton::clicked, this, &MainWindow::onActionThrottleTriggered);
    connect(ui->actionPower, &QPushButton::clicked, this, &MainWindow::onActionPowerTriggered);
    //connect(ui->checkBox, &QCheckBox::stateChanged, this, &MainWindow::editModeFunction);
    connect(ui->PowerOnTrack, &QPushButton::clicked, [=, this](){
        dccExWindow->sendCommand("<1>");
    });
    connect(ui->PowerOffTrack, &QPushButton::clicked, [=, this](){
        dccExWindow->sendCommand("<0>");
    });

    connect(ui->checkBox, &QCheckBox::stateChanged, this, &MainWindow::editMenuEnabled);


    //this->showFullScreen();
}

bool MainWindow::isAnyConnected = false;

MainWindow::~MainWindow() {
    delete dccExWindow;
    delete powerWindow;
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

void MainWindow::toggleTabShow() const {
    //condition on if tab is shown or not
    if (ui->tabWidget->isVisible()) {
        ui->tabWidget->setVisible(false);
    } else {
        ui->tabWidget->setVisible(true);
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
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
    if (watched == this && event->type() == QEvent::HoverMove) {
        auto *mouseEvent = dynamic_cast<QHoverEvent*>(event);
        // Check if the mouse is within 5px from the top if not hide the tabWidget and also check if I am not on the tabWidget
        if (mouseEvent->position().y() >= 10 && !ui->tabWidget->underMouse()) {
            ui->tabWidget->setVisible(false);
            // qDebug() << "Tab widget hidden";
        } else
        {
            ui->tabWidget->setVisible(true);
            // qDebug() << "Tab widget shown";
        }
        return true;
    } else if (watched == ui->tabWidget && event->type() == QEvent::Leave) {
        ui->tabWidget->setVisible(false);
        // qDebug() << "Tab widget hidden LEAVE";
        return true;
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::editMenuEnabled() {
    if (ui->checkBox->isChecked()) {
        if (stationControllWindow && stationControllWindow->ui && stationControllWindow->ui->Refresh && stationControllWindow->ui->ResetRoutes) {
            stationControllWindow->ui->Refresh->show();
            stationControllWindow->ui->ResetRoutes->show();
        }
    } else {
        if (stationControllWindow && stationControllWindow->ui && stationControllWindow->ui->Refresh && stationControllWindow->ui->ResetRoutes) {
            stationControllWindow->ui->Refresh->hide();
            stationControllWindow->ui->ResetRoutes->hide();
        }
    }
}
