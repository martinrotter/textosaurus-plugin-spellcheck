TEMPLATE = lib
CONFIG += unversioned_libname unversioned_soname skip_target_version_ext c++17 warn_on resources_small
CONFIG -= debug_and_release

# Setup specific compiler options.
CONFIG(release, debug|release) {
  message(Building in "release" mode.)

  gcc:QMAKE_CXXFLAGS_RELEASE -= -O2
  clang:QMAKE_CXXFLAGS_RELEASE -= -O2
  gcc:QMAKE_CXXFLAGS_RELEASE *= -O3
  clang:QMAKE_CXXFLAGS_RELEASE *= -O3
}
else {
  message(Building in "debug" mode.)

  DEFINES *= DEBUG=1
  gcc:QMAKE_CXXFLAGS_DEBUG *= -Wall
  clang:QMAKE_CXXFLAGS_DEBUG *= -Wall
}

MOC_DIR = $$OUT_PWD/moc
RCC_DIR = $$OUT_PWD/rcc
UI_DIR = $$OUT_PWD/ui

# Enable various options, including Unicode build.
DEFINES *= QT_DEPRECATED_WARNINGS QT_USE_QSTRINGBUILDER QT_USE_FAST_CONCATENATION QT_USE_FAST_OPERATOR_PLUS UNICODE _UNICODE

# Import libtextosaurus classes and export this plugin classes.
DEFINES *= TEXTOSAURUS_DLLSPEC=Q_DECL_IMPORT TEXTOSAURUS_DLLSPEC_EXPORT=Q_DECL_EXPORT

# Import Scintilla classes and setup path to Scintilla.
DEFINES *= EXPORT_IMPORT_API=Q_DECL_IMPORT
DEFINES *= SCINTILLA_DIR=$${TEXTOSAURUS_INCLUDE}/libtextosaurus/3rd-party/scintilla/

message(Textosaurus repository root folder is: $$TEXTOSAURUS_INCLUDE)
message(Libtextosaurus binary folder is: $$LIBTEXTOSAURUS_BIN_LIB)

# Setup inclusion of (lib)textosaurus, which is needed
# by every plugin. Every plugin must link against libtextosaurus.
INCLUDEPATH +=  $$TEXTOSAURUS_INCLUDE \
                $$TEXTOSAURUS_INCLUDE/libtextosaurus \
                $$TEXTOSAURUS_INCLUDE/libtextosaurus/3rd-party/scintilla/qt/ScintillaEditBase \
                $$TEXTOSAURUS_INCLUDE/libtextosaurus/3rd-party/scintilla/include \
                $$TEXTOSAURUS_INCLUDE/libtextosaurus/3rd-party/scintilla/src

DEPENDPATH += $$LIBTEXTOSAURUS_BIN_LIB

win32: LIBS += -L$$LIBTEXTOSAURUS_BIN_LIB -llibtextosaurus
unix: LIBS += -L$$LIBTEXTOSAURUS_BIN_LIB -ltextosaurus
