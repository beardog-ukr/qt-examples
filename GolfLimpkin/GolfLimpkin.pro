QT += core

TEMPLATE = app

CONFIG += console

TARGET = "golfLimpkinApp"

MOC_DIR = build/moc
OBJECTS_DIR = build/obj
DESTDIR = build/bin

#INCLUDEPATH += $$[QT_INSTALL_HEADERS]

#LIBS += -L$$[QT_INSTALL_LIBS]

HEADERS =
HEADERS += src/BasicLambdas.h
HEADERS += src/LambdaGenerator.h
HEADERS += src/LambdasWithObjects.h
HEADERS += src/ScopeLambdas.h
HEADERS += src/UsualFunctions.h
HEADERS += src/UsualFunctors.h

SOURCES =  src/main.cpp
SOURCES += src/BasicLambdas.cpp
SOURCES += src/LambdaGenerator.cpp
SOURCES += src/LambdasWithObjects.cpp
SOURCES += src/ScopeLambdas.cpp
SOURCES += src/UsualFunctions.cpp
SOURCES += src/UsualFunctors.cpp


message(Qt version: $$[QT_VERSION])
message(Qt is installed in $$[QT_INSTALL_PREFIX])
message(Qt resources can be found in the following locations:)
message(Documentation: $$[QT_INSTALL_DOCS])
message(Header files: $$[QT_INSTALL_HEADERS])
message(Libraries: $$[QT_INSTALL_LIBS])
message(Binary files (executables): $$[QT_INSTALL_BINS])
message(Plugins: $$[QT_INSTALL_PLUGINS])
message(Data files: $$[QT_INSTALL_DATA])
message(Translation files: $$[QT_INSTALL_TRANSLATIONS])
message(Settings: $$[QT_INSTALL_CONFIGURATION])
message(Examples: $$[QT_INSTALL_EXAMPLES])
