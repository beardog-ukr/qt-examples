QT = core

TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle

TARGET = CharlieSparrow

DESTDIR = build/bin
MOC_DIR = build/moc
OBJECTS_DIR = build/obj
RCC_DIR = build/rcc
UI_DIR = build/ui

# ==============================================================================

INCLUDEPATH += "../../src/basic/cpp/"

INCLUDEPATH += "../../src/actions/cpp/"
LIBS += ../actions/build/bin/libCharlieSparrowActions.a

INCLUDEPATH += "../../src/engine/cpp/"
LIBS += ../engine/build/bin/libCharlieSparrowEngine.a

# ==============================================================================

HEADERS =
HEADERS += ../../src/basic/cpp/CharlieSparrowApp.h

SOURCES =  ../../src/basic/cpp/main.cpp
SOURCES += ../../src/basic/cpp/CharlieSparrowApp.cpp
