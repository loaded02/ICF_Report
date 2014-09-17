#-------------------------------------------------
#
# Project created by QtCreator 2014-08-30T22:33:51
#
#-------------------------------------------------

QT       += core gui
QT       += xml
QT       += printsupport
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ICF_Report
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    icfcontroller.cpp \
    patient.cpp \
    therapist.cpp \
    report.cpp \
    function.cpp \
    gui_function.cpp \
    gui_functionform.cpp \
    person.cpp \
    domparser.cpp \
    printwindow.cpp \
    gui_showperson.cpp \
    gui_newperson.cpp

HEADERS  += mainwindow.h \
    icfcontroller.h \
    patient.h \
    therapist.h \
    report.h \
    function.h \
    gui_function.h \
    gui_functionform.h \
    person.h \
    domparser.h \
    printwindow.h \
    gui_showperson.h \
    gui_newperson.h

FORMS    += mainwindow.ui \
    gui_function.ui \
    gui_functionform.ui \
    gui_showperson.ui \
    gui_newperson.ui
