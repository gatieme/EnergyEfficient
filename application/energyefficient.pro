#-------------------------------------------------
#
# Project created by QtCreator 2016-11-13T16:26:23
#
#-------------------------------------------------

QT       += core gui network qt3support

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = energyefficient
TEMPLATE = app


DESTDIR += ./bin
OBJECTS_DIR += ./obj

# for FPGA and qwt-6.1.3
INCLUDEPATH +=  ./CGMonitor2/InlcudeCG   \
                /usr/local/Trolltech/qwt-6.1.3-qt-4.8.0/x86/include
#INCLUDEPATH += /usr/local/Trolltech/4.4.3/arm-none-linux-gnueabi/sys-root/usr/include/
#INCLUDEPATH += /home/cc/ipcamera/x264/include#embeded

# for FPGA and qwt-6.1.3
LIBS += -L./lib/x86 -lfpgaCG_mon    \
        -L/usr/local/Trolltech/qwt-6.1.3-qt-4.8.0/x86/lib
#LIBS += -L./lib/arm -lfpgaCG_mon    \
#        -L/usr/local/Trolltech/qwt-6.1.3-qt-4.8.0/arm/lib

SOURCES += main.cpp\
    fpga/jpeg/JPEGmainwindow.cpp \
    fpga/des/DESmainwindow.cpp \
    fpga/fpgamainwindow.cpp \
    eewidget.cpp \
    fpga/des/common.c \
    fpga/CGMonitor2/ccmessage.cpp \
    fpga/CGMonitor2/CGmainwindow.cpp \
    fpga/CGMonitor2/chunks.cpp \
    fpga/CGMonitor2/commands.cpp \
    fpga/CGMonitor2/FinishedTaskTab.cpp \
    fpga/CGMonitor2/HistorySummaryTab.cpp \
    fpga/CGMonitor2/IniExcc.cpp \
    fpga/CGMonitor2/IOModuleTab.cpp \
    fpga/CGMonitor2/MonitorWidget.cpp \
    fpga/CGMonitor2/OngoingTaskTab.cpp \
    fpga/CGMonitor2/qhexedit.cpp \
    fpga/CGMonitor2/SummaryTab.cpp \
    fpga/CGMonitor2/SupportedOptTab.cpp \
    blcore/blcorewidget.cpp

HEADERS  += \
    fpga/jpeg/JPEGmainwindow.h \
    fpga/des/DESmainwindow.h \
    fpga/fpgaCG.h \
    fpga/fpgamainwindow.h \
    eewidget.h \
    fpga/CGMonitor2/ccmessage.h \
    fpga/CGMonitor2/CGmainwindow.h \
    fpga/CGMonitor2/chunks.h \
    fpga/CGMonitor2/commands.h \
    fpga/CGMonitor2/FinishedTaskTab.h \
    fpga/CGMonitor2/fpgaCGMon.h \
    fpga/CGMonitor2/HistorySummaryTab.h \
    fpga/CGMonitor2/IniEx.h \
    fpga/CGMonitor2/IOModuleTab.h \
    fpga/CGMonitor2/MonitorWidget.h \
    fpga/CGMonitor2/OngoingTaskTab.h \
    fpga/CGMonitor2/qhexedit.h \
    fpga/CGMonitor2/SummaryTab.h \
    fpga/CGMonitor2/SupportedOptTab.h \
    blcore/blcorewidget.h

FORMS    += \
    fpga/jpeg/jpegmainwindow.ui \
    fpga/des/desmainwindow.ui \
    fpga/fpgamainwindow.ui \
    eewidget.ui \
    fpga/CGMonitor2/mainwindow.ui \
    blcore/blcorewidget.ui
