TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += \
        main.cpp \
    login.cpp \
    registertime.cpp \
    usermenu.cpp \
    addsongwindow.cpp \
    showtopgeneral.cpp \
    adminpanel.cpp \
    voteasong.cpp \
    addcomm.cpp \
    showcomm.cpp \
    showcommwindow.cpp \
    banwindow.cpp \
    removesong.cpp

FORMS += \
    login.ui \
    registertime.ui \
    usermenu.ui \
    addsongwindow.ui \
    showtopgeneral.ui \
    adminpanel.ui \
    voteasong.ui \
    addcomm.ui \
    showcomm.ui \
    showcommwindow.ui \
    banwindow.ui \
    removesong.ui

HEADERS += \
    login.h \
    registertime.h \
    usermenu.h \
    addsongwindow.h \
    showtopgeneral.h \
    adminpanel.h \
    voteasong.h \
    addcomm.h \
    showcomm.h \
    showcommwindow.h \
    banwindow.h \
    removesong.h

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += core gui
