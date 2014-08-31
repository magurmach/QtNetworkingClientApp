#-------------------------------------------------
#
# Project created by QtCreator 2014-08-25T08:51:40
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClientSideApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    draganddropwidget.cpp \
    folderhierarchymanager.cpp \
    popdragdropbrowsewidget.cpp \
    resizablerubber.cpp

HEADERS  += mainwindow.h \
    draganddropwidget.h \
    folderhierarchymanager.h \
    popdragdropbrowsewidget.h \
    resizablerubber.h

FORMS    += mainwindow.ui \
    popdragdropbrowsewidget.ui

RESOURCES += \
    AllResource.qrc
