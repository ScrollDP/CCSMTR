#include <QApplication>
#include "MainScreen/MainWindow/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow; // Create an instance of MainWindow
    mainWindow.show(); // Show the MainWindow instance

    return QApplication::exec(); // Start the event loop
}