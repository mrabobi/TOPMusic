TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += \
        main.cpp
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += core gui
QT += sql

FORMS +=

HEADERS +=
