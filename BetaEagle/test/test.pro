QT += core
QT += testlib

TEMPLATE = app

CONFIG += console


TARGET = "testApp"

MOC_DIR = build/moc
OBJECTS_DIR = build/obj
DESTDIR = build/bin

INCLUDEPATH += ../app/src/

HEADERS = src/TestDataProcessor.h
HEADERS += src/TestFileLoader.h
HEADERS += ../app/src/DataProcessor.h
HEADERS += ../app/src/FileLoader.h

SOURCES =  src/TestMain.cpp
SOURCES += src/TestDataProcessor.cpp
SOURCES += src/TestFileLoader.cpp
SOURCES += ../app/src/DataProcessor.cpp
SOURCES += ../app/src/FileLoader.cpp
