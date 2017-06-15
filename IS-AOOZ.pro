#-------------------------------------------------
#
# Project created by QtCreator 2016-11-23T21:10:02
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += charts
CONFIG += c++14
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IS-AOOZ
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    decane.cpp \
    admin.cpp \
    prepare.cpp \
    admin_users.cpp \
    admin_addus.cpp \
    admin_delus.cpp \
    adminbd.cpp \
    klaster.cpp \
    spravka.cpp \
    dynamic.cpp \
    zavcath.cpp \
    analiz.cpp \
    analyzeres.cpp \
    variety.cpp \
    ds.cpp \
    spravkazavcath.cpp \
    spravkadecane.cpp \
    svodanalyz.cpp


HEADERS  += widget.h \
    decane.h \
    admin.h \
    klaster.h \
    prepare.h \
    admin_users.h \
    admin_addus.h \
    admin_delus.h \
    adminbd.h \
    spravka.h \
    dynamic.h \
    zavcath.h \
    analiz.h \
    analyzeres.h \
    vairiety.h \
    ds.h \
    spravkazavcath.h \
    spravkadecane.h \
    svodanalyz.h


FORMS    += widget.ui \
    decane.ui \
    admin.ui \
    prepare.ui \
    admin_users.ui \
    admin_addus.ui \
    admin_delus.ui \
    adminbd.ui \
    klaster.ui \
    spravka.ui \
    dynamic.ui \
    zavcath.ui \
    analiz.ui \
    analyzeres.ui \
    vairiety.ui \
    ds.ui \
    spravkazavcath.ui \
    spravkadecane.ui \
    svodanalyz.ui

RESOURCES += \
    resource.qrc
