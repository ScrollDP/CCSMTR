#include <QApplication>
#include "mainWindow/mainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    mainWindow mainWindow; // Create an instance of mainWindow
    mainWindow.show(); // Show the mainWindow instance

    return QApplication::exec(); // Start the event loop
}