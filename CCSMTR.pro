TEMPLATE = app
CONFIG += c++17
CONFIG -= app_bundle
CONFIG -= qt

QT += core gui widgets serialport

SOURCES += \
    src/main.cpp \
    src/mainWindow/mainWindow.cpp \
    src/connection/DCC-EX/dccEx.cpp \

HEADERS += \
    src/mainWindow/mainWindow.h \
    src/connection/DCC-EX/dccEx.h \

FORMS += \
    src/mainWindow/ui_mainwindow.ui \
    src/connection/DCC-EX/ui_dccEx.ui \

TARGET = CCSMTR
DESTDIR = app