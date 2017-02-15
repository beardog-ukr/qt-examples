QT = core
QT += network
QT += testlib

TEMPLATE = app

CONFIG += console

TARGET = engineTest

DESTDIR = build/bin
MOC_DIR = build/moc
OBJECTS_DIR = build/obj
RCC_DIR = build/rcc
UI_DIR = build/ui

# ==============================================================================
INCLUDEPATH += "../../src/engine/cpp/"
LIBS += ../engine/build/bin/libCharlieSparrowEngine.a

RESOURCES = ../../src/engineTest/rc/TestDoNothing.qrc

INCLUDEPATH += "../../src/engine/cpp/"
LIBS += ../engine/build/bin/libCharlieSparrowEngine.a

HEADERS =
HEADERS += ../../src/engineTest/cpp/TestEngine.h

SOURCES =  ../../src/engineTest/cpp/EngineTestMain.cpp
SOURCES += ../../src/engineTest/cpp/TestEngine.cpp
SOURCES += ../../src/engineTest/cpp/TestDoNothingWorker.cpp
