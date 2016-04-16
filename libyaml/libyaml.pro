#-------------------------------------------------
#
# Project created by QtCreator 2016-04-10T14:34:23
#
#-------------------------------------------------

QT       -= gui

TARGET = libyaml
TEMPLATE = lib
CONFIG += staticlib

include(libyaml.pri)

DEFINES += LIBYAML_LIBRARY

SOURCES += libyaml.cpp \
    yamlobject.cpp

HEADERS += libyaml.h\
        libyaml_global.h \
    yamlobject.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

QT       -= gui
