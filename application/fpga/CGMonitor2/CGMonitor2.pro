#-------------------------------------------------
#
# Project created by QtCreator 2015-09-02T10:23:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CGMonitor2
TEMPLATE = app

INCLUDEPATH += ./InlcudeCG
LIBS += -L./ -lfpgaCG_mon


SOURCES += main.cpp\
        mainwindow.cpp \
    SummaryTab.cpp \
    MonitorWidget.cpp \
    SupportedOptTab.cpp \
    OngoingTaskTab.cpp \
    IOModuleTab.cpp \
    HistorySummaryTab.cpp \
    FinishedTaskTab.cpp \
    qhexedit.cpp \
    chunks.cpp \
    commands.cpp \
    IniEx.cpp \
    CGmainwindow.cpp

HEADERS  += mainwindow.h \
    SummaryTab.h \
    MonitorWidget.h \
    SupportedOptTab.h \
    OngoingTaskTab.h \
    IOModuleTab.h \
    HistorySummaryTab.h \
    FinishedTaskTab.h \
    qhexedit.h \
    chunks.h \
    commands.h \
    fpgaCGMon.h \
    IniEx.h \
    CGmainwindow.h

FORMS    += \
    mainwindow.ui
