#-------------------------------------------------
#
# Project created by QtCreator 2016-02-17T09:51:10
#
#-------------------------------------------------

QT          +=  core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport multimedia serialport

TARGET      =   FESS-GUI
TEMPLATE    =   app


SOURCES     +=  main.cpp \
                mainwindow.cpp \
                qcustomplot.cpp \
                setpassworddialog.cpp \
                graphoperation.cpp \
                flywheeloperation.cpp \
                recordingoperation.cpp \
                serial.cpp \
    demo.cpp \
    interfacemanager.cpp \
    transmitbuffer.cpp

HEADERS     +=  mainwindow.h \
                qcustomplot.h \
                setpassworddialog.h \
                graphoperation.h \
                flywheeloperation.h \
                recordingoperation.h \
                interface.h \
                serial.h \
                commands.h \
    demo.h \
    interfacemanager.h \
    transmitbuffer.h

FORMS       +=  mainwindow.ui \
                setpassworddialog.ui

DISTFILES   +=  fess.rc

RC_FILE     =   fess.rc

RESOURCES   +=  sounds.qrc

CONFIG      +=  c++11
