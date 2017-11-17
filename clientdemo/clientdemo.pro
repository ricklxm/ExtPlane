QT += core network
QT -= gui

CONFIG += c++11

TARGET = clientdemo
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    explanedemo.cpp

LIBS += -L$$PWD/libs -lextplane-client-qt

INCLUDEPATH += include

HEADERS += \
    explanedemo.h
