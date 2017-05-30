QT = core
QT += gui
QT += widgets

TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle

TARGET = HiddenVulture

DESTDIR = build/bin
MOC_DIR = build/moc
OBJECTS_DIR = build/obj
RCC_DIR = build/rcc
UI_DIR = build/ui

# ==============================================================================

INCLUDEPATH += "../../src/basic/cpp/"

INCLUDEPATH += "../../src/c5/cpp/"
LIBS += ../c5/build/bin/libHiddenVultureC5.a

INCLUDEPATH += "../../src/engine/cpp/"
LIBS += ../engine/build/bin/libHiddenVultureEngine.a
PRE_TARGETDEPS += "$$_PRO_FILE_PWD_/../engine/build/bin/libHiddenVultureEngine.a"

# ==============================================================================

HEADERS =
HEADERS += ../../src/basic/cpp/HiddenVultureApp.h

SOURCES =  ../../src/basic/cpp/main.cpp
SOURCES += ../../src/basic/cpp/HiddenVultureApp.cpp

# ==============================================================================

INCLUDEPATH += C:\otherProg\opencv3.2.0-build\install\include
LIBS += -LC:\otherProg\opencv3.2.0-build\install\x86\mingw\lib
LIBS += -lopencv_core320.dll
LIBS += -lopencv_highgui320.dll
LIBS += -lopencv_imgcodecs320.dll
LIBS += -lopencv_imgproc320.dll
LIBS += -lopencv_features2d320.dll
LIBS += -lopencv_calib3d320.dll
LIBS += -lopencv_video320.dll
LIBS += -lopencv_videoio320.dll
