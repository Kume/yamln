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
    yamlobject.cpp \
    libyamlexception.cpp \
    yamlpath.cpp \
    action/yamlaction.cpp \
    action/modifyyamlaction.cpp

HEADERS += libyaml.h\
    yamlobject.h \
    libyamlexception.h \
    yamlpath.h \
    action/yamlaction.h \
    action/modifyyamlaction.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
