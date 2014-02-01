#-------------------------------------------------
#
# Project created by QtCreator 2014-01-30T23:08:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FloImageSharerUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    configurator.cpp \
    runtime.cpp

HEADERS  += mainwindow.h \
    configurator.h \
    runtime.h

FORMS    += mainwindow.ui

CONFIG += c++11
