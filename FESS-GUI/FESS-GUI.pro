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
                flywheeloperation.cpp \
                recordingoperation.cpp \
                transmitbuffer.cpp \
                conversions.cpp \
                flypacket.cpp \
                demodevice.cpp \
                serialdevice.cpp \
                graph.cpp \
    commoninterfaceselector.cpp \
    commoninterfacemanager.cpp

HEADERS     +=  mainwindow.h \
                qcustomplot.h \
                setpassworddialog.h \
                flywheeloperation.h \
                recordingoperation.h \
                commands.h \
                transmitbuffer.h \
                commondeviceinterface.h \
                datatypes.h \
                conversions.h \
                flypacket.h \
                demodevice.h \
                serialdevice.h \
                graph.h \
    commoninterfaceselector.h \
    commoninterfacemanager.h

FORMS       +=  mainwindow.ui \
                setpassworddialog.ui \
    commoninterfaceselector.ui

DISTFILES   +=  fess.rc

RC_FILE     =   fess.rc

RESOURCES   +=  sounds.qrc

CONFIG      +=  c++11
