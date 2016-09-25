#-------------------------------------------------
#
# Project created by QtCreator 2016-07-18T19:37:17
#
#-------------------------------------------------

QT       -= gui

TARGET = activeYaml
TEMPLATE = lib
CONFIG += staticlib

include(libyaml.pri)

DEFINES += LIBYAML_LIBRARY

SOURCES += \
    yamlobject.cpp \
    activeyamlexception.cpp \
    yamlpath.cpp \
    action/yamlaction.cpp \
    action/modifyyamlaction.cpp \
    yamlmanager.cpp

HEADERS += activeyaml.h \
    yamlobject.h \
    activeyamlexception.h \
    yamlpath.h \
    action/yamlaction.h \
    action/modifyyamlaction.h \
    yamlmanager.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
