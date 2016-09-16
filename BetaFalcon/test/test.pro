QT += core
QT += testlib

TEMPLATE = app

CONFIG += console

TARGET = "testApp"

MOC_DIR = build/moc
OBJECTS_DIR = build/obj
DESTDIR = build/bin

RESOURCES = testDataFiles.qrc

INCLUDEPATH += ../app/src/

HEADERS = src/TestFileProcessor.h
HEADERS += ../app/src/FileProcessor.h

SOURCES =  src/TestMain.cpp
SOURCES += src/TestFileProcessor.cpp
SOURCES += ../app/src/FileProcessor.cpp
