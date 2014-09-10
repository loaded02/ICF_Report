#-------------------------------------------------
#
# Project created by QtCreator 2014-08-30T22:33:51
#
#-------------------------------------------------

QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ICF_Report
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    newpatientform.cpp \
    icfcontroller.cpp \
    patient.cpp \
    therapist.cpp \
    report.cpp \
    function.cpp \
    context.cpp \
    structure.cpp \
    partizipation.cpp \
    gui_function.cpp \
    gui_functionform.cpp \
    person.cpp \
    domparser.cpp

HEADERS  += mainwindow.h \
    newpatientform.h \
    icfcontroller.h \
    patient.h \
    therapist.h \
    report.h \
    function.h \
    context.h \
    structure.h \
    partizipation.h \
    gui_function.h \
    gui_functionform.h \
    person.h \
    domparser.h

FORMS    += mainwindow.ui \
    newpatientform.ui \
    gui_function.ui \
    gui_functionform.ui
