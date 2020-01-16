#-------------------------------------------------
#
# Project created by QtCreator 2014-09-15T17:55:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_SAP_TERMINAL
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    answer_box.cpp \
    quary_box.cpp \
    serialcomm.cpp

HEADERS  += mainwindow.h \
    answer_box.h \
    quary_box.h \
    serialcomm.h

FORMS    += mainwindow.ui

 include(qextserialport-1.2beta2/src/qextserialport.pri)

RESOURCES += \
    #../../terminal/resourse.qrc
    resource.qrc
