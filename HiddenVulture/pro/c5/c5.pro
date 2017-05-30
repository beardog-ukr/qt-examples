QT = core

TEMPLATE = lib

CONFIG += console
CONFIG += static
CONFIG -= app_bundle

TARGET = HiddenVultureC5

DESTDIR = build/bin
MOC_DIR = build/moc
OBJECTS_DIR = build/obj
RCC_DIR = build/rcc
UI_DIR = build/ui

unix:QMAKE_CXXFLAGS += "-std=c++0x"

# ==============================================================================

#INCLUDEPATH += "../../src/engine/cpp/"

# ==============================================================================

HEADERS =
HEADERS += ../../src/c5/cpp/FiveCatsLogger.h

SOURCES =
SOURCES += ../../src/c5/cpp/FiveCatsLogger.cpp
