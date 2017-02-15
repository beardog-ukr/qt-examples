QT = core
QT += network
QT += xml

TEMPLATE = app

CONFIG += console
CONFIG += debug

TARGET = FoxtrotPenguin

DESTDIR = build/bin
MOC_DIR = build/moc
OBJECTS_DIR = build/obj
RCC_DIR = build/rcc
UI_DIR = build/ui

# ==============================================================================
INCLUDEPATH += "./src/"

#INCLUDEPATH += "../../src/zlib128-dll/include/"
#LIBS += -L"$$_PRO_FILE_PWD_/../../src/zlib128-dll/lib/" -lzdll
# ==============================================================================

HEADERS =
HEADERS += ./src/FoxtrotPenguin.h

SOURCES =  ./src/main.cpp
SOURCES += ./src/FoxtrotPenguin.cpp
