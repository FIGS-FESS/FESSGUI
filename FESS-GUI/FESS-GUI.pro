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
<<<<<<< HEAD
    parametersettings.cpp

HEADERS  += mainwindow.h \
    parametersettings.h
=======
        qcustomplot.cpp \
    rtg.cpp

HEADERS  += mainwindow.h \
         qcustomplot.h \
    rtg.h
>>>>>>> refs/remotes/origin/master

<<<<<<< HEAD
FORMS    += mainwindow.ui \
    parametersettings.ui
=======
FORMS    += mainwindow.ui

DISTFILES += \
    fess.rc

RC_FILE = fess.rc
<<<<<<< HEAD
>>>>>>> refs/remotes/origin/master
=======

RESOURCES += \
    sounds.qrc

>>>>>>> refs/remotes/origin/master
