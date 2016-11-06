TEMPLATE = app

QT += qml quick webengine
CONFIG += c++11

SOURCES += main.cpp \
    uiviewmodel/uiviewmodel.cpp \
    uiviewmodel/textuiviewmodel.cpp \
    uiviewmodel/formuiviewmodel.cpp \
    uiviewmodel/rootuiviewmodel.cpp \
    uiviewmodel/uiviewmodellist.cpp \
    exceptions/yamlnexception.cpp \
    exceptions/yamlobjectexception.cpp \
    uiviewmodel/formelementuiviewmodel.cpp \
    uiviewmodel/tableuiviewmodel.cpp \
    uiviewmodel/tablerowuiviewmodel.cpp \
    uiviewmodel/tableheaderuiviewmodel.cpp \
    exceptions/uidefinitionexception.cpp \
    uiviewmodel/checkboxuiviewmodel.cpp \
    uiviewmodel/tablecelluiviewmodel.cpp

RESOURCES += qml.qrc \
    samples.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../activeYaml/release/ -lactiveYaml
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../activeYaml/debug/ -lactiveYaml
else:unix: LIBS += -L$$OUT_PWD/../activeYaml/ -lactiveYaml

INCLUDEPATH += $$PWD/../activeYaml
DEPENDPATH += $$PWD/../activeYaml

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../activeYaml/release/libactiveYaml.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../activeYaml/debug/libactiveYaml.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../activeYaml/release/activeYaml.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../activeYaml/debug/activeYaml.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../activeYaml/libactiveYaml.a

HEADERS += \
    uiviewmodel/uiviewmodel.h \
    uiviewmodel/textuiviewmodel.h \
    uiviewmodel/formuiviewmodel.h \
    uiviewmodel/rootuiviewmodel.h \
    uiviewmodel/uiviewmodellist.h \
    exceptions/yamlnexception.h \
    exceptions/yamlobjectexception.h \
    uiviewmodel/formelementuiviewmodel.h \
    uiviewmodel/tableuiviewmodel.h \
    uiviewmodel/tablerowuiviewmodel.h \
    uiviewmodel/tableheaderuiviewmodel.h \
    exceptions/uidefinitionexception.h \
    uiviewmodel/checkboxuiviewmodel.h \
    uiviewmodel/tablecelluiviewmodel.h

