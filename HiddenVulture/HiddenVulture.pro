TEMPLATE = subdirs

c5.subdir = pro/c5
c5.target = c5-lib

engine.subdir = pro/engine
engine.target = engine-lib
engine.depends = c5-lib

basic.subdir = pro/basic
basic.target = basic-app
basic.depends = c5-lib
basic.depends = engine-lib

SUBDIRS =
SUBDIRS += engine
SUBDIRS += c5
SUBDIRS += basic

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
message("===============================================")
