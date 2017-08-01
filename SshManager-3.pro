QT += widgets

CONFIG += c++11

TARGET = SshManager-3
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += src/main.cpp \
    src/window.cpp \
    src/config.cpp \
    src/windowconfig.cpp \
    src/commandconfig.cpp \
    src/connection.cpp \
    src/connectionlistmodel.cpp

HEADERS += \
    src/window.h \
    src/config.h \
    src/windowconfig.h \
    src/commandconfig.h \
    src/connection.h \
    src/connectionlistmodel.h

DISTFILES += \
    /icon.png \
    README.md \
    screenshot.png \
    .travis.yml

RESOURCES += \
    resources.qrc
