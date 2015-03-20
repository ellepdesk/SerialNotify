#-------------------------------------------------
#
# Project created by QtCreator 2015-02-09T10:48:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialNotifier
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serialupdater.cpp \
    updater.cpp

HEADERS  += mainwindow.h \
    updater.h \
    serialupdater.h

FORMS    += mainwindow.ui

RESOURCES += \
    serialnotifier.qrc

QT += serialport
