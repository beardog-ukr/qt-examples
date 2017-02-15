QT = core

TEMPLATE = lib

CONFIG += console
CONFIG += static
CONFIG -= app_bundle

TARGET = CharlieSparrowEngine

DESTDIR = build/bin
MOC_DIR = build/moc
OBJECTS_DIR = build/obj
RCC_DIR = build/rcc
UI_DIR = build/ui

HEADERS =
HEADERS += ../../src/engine/cpp/DoNothingWorker.h

SOURCES =
SOURCES += ../../src/engine/cpp/DoNothingWorker.cpp
