#### This is main project file of plugin for Textosaurus.
##
## !!! Always include file "https://github.com/martinrotter/textosaurus-plugin-example/blob/master/plugin-common-setup.pri"
## in this project like this:
##
##   include($$PWD/plugin-common-setup.pri)
##
#### How to compile (use A or B)
##
## A) Download latest prebuilt release of Textosaurus (all C++ header files and *{dll,lib} files are bundled in it).
## B) Compiled Textosaurus from source.
##
## Every plugin must link against libtextosaurus library.
##
## QMake usage: qmake "TEXTOSAURUS_INCLUDE=<include-headers-root-folder>" "LIBTEXTOSAURUS_BIN_LIB=<folder-with-dll-lib-so>"
## Example: qmake "TEXTOSAURUS_INCLUDE=c:/textosaurus/include" "LIBTEXTOSAURUS_BIN_LIB=c:/my-programs/textosaurus"

include($$PWD/plugin-common-setup.pri)

unix|mac {
  TARGET = textosaurus-spellcheck
}
else {
  TARGET = libtextosaurus-spellcheck
}

QT *= widgets

SOURCES += \
        exampleplugin.cpp

HEADERS += \
        exampleplugin.h

DISTFILES += \
        plugin.json

# Link to Hunspell.
INCLUDEPATH +=  hunspell/include

DEPENDPATH += $$PWD/hunspell/lib/windows_debug

win32: LIBS += -L$$PWD/hunspell/lib/windows_debug -llibhunspell
unix: LIBS += -L$$LIBTEXTOSAURUS_BIN_LIB -lhunspell
