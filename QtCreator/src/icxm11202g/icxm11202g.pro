QT += widgets
TEMPLATE = lib
DEFINES += ICXM11202G_LIBRARY

CONFIG += c++11 qt

TEMPLATE += fakelib
FAKELIBNAME = $$qtLibraryTarget(ICXM11202G)
TEMPLATE -= fakelib

TARGET = $$FAKELIBNAME

include(../../common.pri)
include(../qtwinmigrate/qtwinmigrate.pri)

DESTDIR = $$QTTOMFC_LIBDIR
win32 {
    DLLDESTDIR = $$QTTOMFC_BINDIR
    QMAKE_DISTCLEAN += $$QTTOMFC_BINDIR\\$$FAKELIBNAME.dll
}

SOURCES += \
    QExApp.cpp \
    icxm11202g.cpp \
    icxm11202gsetting.cpp

HEADERS += \
    QExApp.h \
    icxm11202g_global.h \
    icxm11202g.h \
    icxm11202gsetting.h

FORMS += \
    icxm11202gsetting.ui
