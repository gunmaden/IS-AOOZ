#-------------------------------------------------
#
# Project created by QtCreator 2016-11-23T21:10:02
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += charts

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
    spravka.cpp


HEADERS  += widget.h \
    decane.h \
    admin.h \
    klaster.h \
    prepare.h \
    admin_users.h \
    admin_addus.h \
    admin_delus.h \
    adminbd.h \
    spravka.h


FORMS    += widget.ui \
    decane.ui \
    admin.ui \
    prepare.ui \
    admin_users.ui \
    admin_addus.ui \
    admin_delus.ui \
    adminbd.ui \
    klaster.ui \
    spravka.ui

RESOURCES += \
    resource.qrc
