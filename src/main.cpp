#include <QApplication>
#include "MainScreen/MainWindow/MainWindow.h"
#include <QDebug>
#include <QFile>
#include <QDomDocument>
#include <QRegularExpression>

void myMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    switch (type) {
        case QtDebugMsg:
            //fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
            fprintf(stderr, "Debug: %s\n", localMsg.constData());
            break;
        case QtInfoMsg:
            fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
            break;
        case QtWarningMsg:
            fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
            break;
        case QtCriticalMsg:
            fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
            break;
        case QtFatalMsg:
            fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
            abort();
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    qInstallMessageHandler(myMessageHandler);


    MainWindow mainWindow; // Create an instance of MainWindow
    mainWindow.show(); // Show the MainWindow instance

    return QApplication::exec(); // Start the event loop
}