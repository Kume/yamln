TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp

RESOURCES += qml.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libyaml/release/ -llibyaml
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libyaml/debug/ -llibyaml
else:unix: LIBS += -L$$OUT_PWD/../libyaml/ -llibyaml

INCLUDEPATH += $$PWD/../libyaml
DEPENDPATH += $$PWD/../libyaml

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libyaml/release/liblibyaml.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libyaml/debug/liblibyaml.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libyaml/release/libyaml.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libyaml/debug/libyaml.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../libyaml/liblibyaml.a
