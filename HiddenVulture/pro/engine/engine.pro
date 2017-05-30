QT = core
QT += gui
QT += widgets

TEMPLATE = lib

CONFIG += console
CONFIG += static
CONFIG -= app_bundle

TARGET = HiddenVultureEngine

unix:QMAKE_CXXFLAGS += "-std=c++0x"

DESTDIR = build/bin
MOC_DIR = build/moc
OBJECTS_DIR = build/obj
RCC_DIR = build/rcc
UI_DIR = build/ui

INCLUDEPATH += "../../src/c5/cpp/"
LIBS += ../c5/build/bin/libHiddenVultureC5.a

win32 {
  INCLUDEPATH += C:\otherProg\opencv3.2.0-build\install\include
  LIBS += -LC:\otherProg\opencv3.2.0-build\install\x86\mingw\lib
  LIBS += -lopencv_core320.dll
  LIBS += -lopencv_highgui320.dll
  LIBS += -lopencv_imgcodecs320.dll
  LIBS += -lopencv_imgproc320.dll
  LIBS += -lopencv_features2d320.dll
  LIBS += -lopencv_video320.dll
  LIBS += -lopencv_videoio320.dll
}

unix {
  INCLUDEPATH += /home/m1user/prog/opencv/opencv-3.2.0_install_A/include

  LIBS += -L/home/m1user/prog/opencv/opencv-3.2.0_install_A/lib/
  LIBS += -lopencv_core 
  LIBS += -lopencv_highgui 
  LIBS += -lopencv_imgproc 
  LIBS += -lopencv_imgcodecs
  LIBS += -lopencv_video 
  LIBS += -lopencv_videoio 
  LIBS += -lopencv_features2d 
}

HEADERS =
HEADERS += ../../src/engine/cpp/MainForm.h
HEADERS += ../../src/engine/cpp/PlayingOptions.h
HEADERS += ../../src/engine/cpp/VideoPanel.h
HEADERS += ../../src/engine/cpp/VideoReader.h


SOURCES =
SOURCES += ../../src/engine/cpp/MainForm.cpp
SOURCES += ../../src/engine/cpp/PlayingOptions.cpp
SOURCES += ../../src/engine/cpp/VideoPanel.cpp
SOURCES += ../../src/engine/cpp/VideoReader.cpp

