#-------------------------------------------------
#
# Project created by QtCreator 2016-11-23T21:10:02
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IS-AOOZ
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    decane.cpp \
    admin.cpp \
    admin_users.cpp \
    admin_addus.cpp \
    admin_delus.cpp \
    adminbd.cpp
    klaster.cpp


HEADERS  += widget.h \
    decane.h \
    admin.h \
    admin_users.h \
    admin_addus.h \
    admin_delus.h \
    adminbd.h
    klaster.h


FORMS    += widget.ui \
    decane.ui \
    admin.ui \
    admin_users.ui \
    admin_addus.ui \
    admin_delus.ui \
    adminbd.ui
    klaster.ui
