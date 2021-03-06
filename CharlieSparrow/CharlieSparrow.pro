TEMPLATE = subdirs

engine.subdir = pro/engine
engine.target = engine-lib

engineTest.subdir = pro/engineTest
engineTest.target = engine-test-app
engineTest.depends = engine-lib

actions.subdir = pro/actions
actions.target = actions-lib
actions.depends = engine-lib

basic.subdir = pro/basic
basic.target = basic-app
basic.depends = actions-lib

SUBDIRS =
SUBDIRS += engine
SUBDIRS += engineTest
SUBDIRS += actions
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
