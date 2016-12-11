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
    klaster.cpp \
    prepare.cpp

HEADERS  += widget.h \
    decane.h \
    admin.h \
    klaster.h \
    prepare.h

FORMS    += widget.ui \
    decane.ui \
    admin.ui \
    klaster.ui \
    prepare.ui
