#-------------------------------------------------
#
# Project created by QtCreator 2016-04-17T00:53:15
#
#-------------------------------------------------

QT       -= gui

TARGET = test
TEMPLATE = lib
CONFIG += staticlib

SOURCES +=

HEADERS +=
unix {
    target.path = /usr/lib
    INSTALLS += target
}
