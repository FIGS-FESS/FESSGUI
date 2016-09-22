#-------------------------------------------------
#
# Project created by QtCreator 2016-02-17T09:51:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport multimedia

TARGET = FESS-GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        qcustomplot.cpp \
    setpassworddialog.cpp \
    graphoperation.cpp \
    flywheeloperation.cpp

HEADERS  += mainwindow.h \
         qcustomplot.h \
    setpassworddialog.h \
    graphoperation.h \
    flywheeloperation.h

FORMS    += mainwindow.ui \
    setpassworddialog.ui

DISTFILES += \
    fess.rc

RC_FILE = fess.rc

RESOURCES += \
    sounds.qrc
