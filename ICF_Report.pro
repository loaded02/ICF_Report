#-------------------------------------------------
#
# Project created by QtCreator 2014-08-30T22:33:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ICF_Report
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    functions.cpp \
    functionform.cpp \
    newpatientform.cpp

HEADERS  += mainwindow.h \
    functions.h \
    functionform.h \
    newpatientform.h

FORMS    += mainwindow.ui \
    functions.ui \
    functionform.ui \
    newpatientform.ui
