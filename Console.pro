#-------------------------------------------------
#
# Project created by QtCreator 2015-03-01T16:19:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Console
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    keyreturnevent.cpp \
    commandhandler.cpp

HEADERS  += mainwindow.h \
    keyreturnevent.h \
    commandhandler.h

FORMS    += mainwindow.ui
