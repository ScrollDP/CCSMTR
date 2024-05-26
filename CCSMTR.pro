TEMPLATE = app
CONFIG += c++17
CONFIG -= app_bundle
CONFIG -= qt

QT += core gui widgets serialport

SOURCES += \
    src/main.cpp \
    src/mainWindow/mainWindow.cpp \
    src/connection/DCC-EX/dccEx.cpp \
    src/connection/Intelibox_I/intelibox_I.cpp

HEADERS += \
    src/mainWindow/mainWindow.h \
    src/connection/DCC-EX/dccEx.h \
    src/connection/Intelibox_I/intelibox_I.h

FORMS += \
    src/mainWindow/ui_mainwindow.ui \
    src/connection/DCC-EX/ui_dccEx.ui \
    src/connection/Intelibox_I/ui_intelibox_I.ui

TARGET = CCSMTR
DESTDIR = app