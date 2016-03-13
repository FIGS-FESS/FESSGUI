#-------------------------------------------------
#
# Project created by QtCreator 2016-02-12T15:05:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = FESS-GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        qcustomplot.cpp

HEADERS  += mainwindow.h \
         qcustomplot.h

FORMS    += mainwindow.ui

DISTFILES += \
    fess.rc

RC_FILE = fess.rc
