#-------------------------------------------------
#
# Project created by QtCreator 2015-07-10T14:11:01
#
#-------------------------------------------------

QT       += opengl

QT       -= gui

TARGET = PUTPraktyki2015
TEMPLATE = lib

DEFINES += PUTPRAKTYKI2015_LIBRARY

SOURCES += main.cpp

HEADERS += main.h\
        putpraktyki2015_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
