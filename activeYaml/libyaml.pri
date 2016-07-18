defineReplace(mode) {
    CONFIG(release, debug|release):return(release)
    else:return(debug)
}

CONFIG += c++11

INCLUDEPATH += \
    $$PWD/libyaml/include \
    $$PWD/libyaml/src

DEFINES += HAVE_CONFIG_H YAML_DECLARE_STATIC
INCLUDEPATH += $$PWD/libyaml/win32

SOURCES += \
    $$PWD/libyaml/src/api.c \
    $$PWD/libyaml/src/dumper.c \
    $$PWD/libyaml/src/emitter.c \
    $$PWD/libyaml/src/loader.c \
    $$PWD/libyaml/src/parser.c \
    $$PWD/libyaml/src/reader.c \
    $$PWD/libyaml/src/scanner.c \
    $$PWD/libyaml/src/writer.c
