#-------------------------------------------------
#
# Project created by QtCreator 2016-01-22T21:13:26
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11
QT += opengl


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled5
TEMPLATE = app


SOURCES += main.cpp\
    glwidget.cpp \
    OsamaDistance.cpp \
    Osama.cpp

HEADERS  += \
    StdAfx.h \
    glwidget.h \
    OsamaDistance.h \
    Osama.h

FORMS    += mainwindow.ui \
    glwidget.ui \
    osama.ui


