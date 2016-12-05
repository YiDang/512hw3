#-------------------------------------------------
#
# Project created by QtCreator 2016-12-03T17:31:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gtd_map.cpp \
    node.cpp \
    datagen.cpp \
    sse.cpp \
    dataloader.cpp \
    experi.cpp

HEADERS  += mainwindow.h \
    gtd_map.h \
    node.h \
    datagen.h \
    sse.h \
    dataloader.h \
    experi.h

FORMS    += mainwindow.ui
