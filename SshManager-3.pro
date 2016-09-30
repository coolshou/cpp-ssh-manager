QT += widgets

CONFIG += c++11

TARGET = SshManager-3
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    window.cpp \
    config.cpp \
    windowconfig.cpp \
    commandconfig.cpp \
    connection.cpp \
    connectionlistmodel.cpp

HEADERS += \
    window.h \
    config.h \
    windowconfig.h \
    commandconfig.h \
    connection.h \
    connectionlistmodel.h

DISTFILES += \
    /icon.png
