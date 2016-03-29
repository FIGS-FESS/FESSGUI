#-------------------------------------------------
#
# Project created by QtCreator 2016-02-17T09:51:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FESS-GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    parametersettings.cpp

HEADERS  += mainwindow.h \
    parametersettings.h

<<<<<<< HEAD
FORMS    += mainwindow.ui \
    parametersettings.ui
=======
FORMS    += mainwindow.ui

DISTFILES += \
    fess.rc

RC_FILE = fess.rc
>>>>>>> refs/remotes/origin/master
