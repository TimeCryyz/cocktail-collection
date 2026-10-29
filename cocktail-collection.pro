QT       += core gui widgets

CONFIG += c++17 console
CONFIG -= app_bundle

CODECFORTR = UTF-8
QMAKE_CXXFLAGS += -finput-charset=UTF-8 -fexec-charset=UTF-8

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/strengthchartwidget.cpp \
    models/cocktailmodel.cpp

HEADERS += \
    src/mainwindow.h \
    src/strengthchartwidget.h \
    models/cocktailmodel.h