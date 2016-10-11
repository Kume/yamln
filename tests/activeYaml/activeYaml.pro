#-------------------------------------------------
#
# Project created by QtCreator 2016-07-16T20:52:09
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_activeyamltest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    tst_yamlobjecttest.cpp \
    tst_main.cpp \
    tst_yamlactiontest.cpp \
    tst_yamlpathtest.cpp \
    tst_yamlmanagertest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../activeYaml/release/ -lactiveYaml
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../activeYaml/debug/ -lactiveYaml
else:unix: LIBS += -L$$OUT_PWD/../../activeYaml/ -lactiveYaml

INCLUDEPATH += $$PWD/../../activeYaml
DEPENDPATH += $$PWD/../../activeYaml

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../activeYaml/release/libactiveYaml.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../activeYaml/debug/libactiveYaml.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../activeYaml/release/activeYaml.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../activeYaml/debug/activeYaml.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../activeYaml/libactiveYaml.a

HEADERS += \
    tst_yamlobjecttest.h \
    tst_yamlactiontest.h \
    tst_yamlpathtest.h \
    tst_yamlmanagertest.h
