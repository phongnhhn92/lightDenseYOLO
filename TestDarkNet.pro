#-------------------------------------------------
#
# Project created by QtCreator 2018-06-12T23:16:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestDarkNet
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    yolo_v2_class.h

FORMS    += mainwindow.ui


LIBS += `pkg-config opencv --libs`\



unix:!macx: LIBS += -L$$PWD/./ -ldarknet

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
