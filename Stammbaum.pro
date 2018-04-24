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
        src/ui/mainwindow.cpp \
        src/db/dbmanager.cpp \
        src/people/person.cpp \
        src/people/event.cpp \
        src/ui/editdialog.cpp \
        src/ui/editperson.cpp \
        src/people/base.cpp \
        src/ui/eventwidget.cpp \
        src/ui/editevent.cpp \
    src/people/parent.cpp \
    src/ui/parentwidget.cpp \
    src/ui/editparent.cpp

HEADERS += \
        src/ui/mainwindow.h \
        src/db/dbmanager.h \
        src/people/person.h \
        src/people/event.h \
        src/ui/editdialog.h \
        src/ui/editperson.h \
        src/people/base.h \
        src/ui/eventwidget.h \
        src/ui/editevent.h \
    src/people/parent.h \
    src/ui/parentwidget.h \
    src/ui/editparent.h

FORMS += \
        src/ui/mainwindow.ui \
        src/ui/editperson.ui \
        src/ui/eventwidget.ui \
        src/ui/editevent.ui \
    src/ui/parentwidget.ui \
    src/ui/editparent.ui

SUBDIRS += \
        stammbaum.pro

DISTFILES += \
        README.md

RESOURCES += \
        res/stammbaum.qrc
