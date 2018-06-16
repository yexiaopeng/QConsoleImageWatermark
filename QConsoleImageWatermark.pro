QT += core
#QT -= gui

QT += gui

QT+=widgets

TARGET = QConsoleImageWatermark
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

DISTFILES += \
    README.md \
    123.jpeg

