QT += core gui widgets printsupport

CONFIG += c++17
TARGET = BDT220new
TEMPLATE = app

SOURCES += \
    main.cpp \
    model_layers.cpp \
    datamanager.cpp \
    mainwindow.cpp

HEADERS += \
    model_layers.h \
    datamanager.h \
    mainwindow.h

FORMS  += \
    mainwindow.ui

# MSVC: 强制源文件按 UTF-8 解析 (MSVC 2015 Update 3+)
msvc:QMAKE_CXXFLAGS += /utf-8
