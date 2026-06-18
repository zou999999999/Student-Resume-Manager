QT       += core gui printsupport widgets

CONFIG   += c++17 console
CONFIG   -= app_bundle
TARGET    = test_runner
TEMPLATE  = app

SOURCES += \
    test_runner.cpp \
    model_layers.cpp \
    datamanager.cpp

HEADERS += \
    model_layers.h \
    datamanager.h

# MSVC: 强制源文件按 UTF-8 解析
msvc:QMAKE_CXXFLAGS += /utf-8
