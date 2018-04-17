#-------------------------------------------------
#
# Project created by QtCreator 2018-04-12T12:18:03
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stammbaum
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += -Werror -Wall -Wextra -pedantic -std=c++11

INCLUDEPATH += $$PWD/src

SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
        src/db/dbmanager.cpp \
        src/person/person.cpp \
        src/editperson.cpp

HEADERS += \
        src/mainwindow.h \
        src/db/dbmanager.h \
        src/person/person.h \
        src/editperson.h

FORMS += \
        src/mainwindow.ui \
        src/editperson.ui

SUBDIRS += \
        stammbaum.pro

DISTFILES += \
    README.md

RESOURCES += \
    res/stammbaum.qrc
