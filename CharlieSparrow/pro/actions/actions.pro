QT = core

TEMPLATE = lib

CONFIG += console
CONFIG += static
CONFIG -= app_bundle

TARGET = CharlieSparrowActions

DESTDIR = build/bin
MOC_DIR = build/moc
OBJECTS_DIR = build/obj
RCC_DIR = build/rcc
UI_DIR = build/ui

# ==============================================================================

INCLUDEPATH += "../../src/engine/cpp/"
#LIBS += ../engine/build/bin/libCharlieSparrowEngine.a

# ==============================================================================

HEADERS =
HEADERS += ../../src/actions/cpp/ActionBasic.h
HEADERS += ../../src/actions/cpp/ActionsStatic.h
HEADERS += ../../src/actions/cpp/DoNothingAction.h

SOURCES =
SOURCES += ../../src/actions/cpp/ActionBasic.cpp
SOURCES += ../../src/actions/cpp/ActionsStatic.cpp
SOURCES += ../../src/actions/cpp/DoNothingAction.cpp
