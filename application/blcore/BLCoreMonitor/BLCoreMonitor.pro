#-------------------------------------------------
#
# Project created by QtCreator 2016-11-21T16:50:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BLCoreMonitor
TEMPLATE = app


# for qwt-6.1.3
INCLUDEPATH += /usr/local/Trolltech/qwt-6.1.3-qt-4.8.0/x86/include
LIBS += -L/usr/local/Trolltech/qwt-6.1.3-qt-4.8.0/x86/lib -lqwt
#LIBS += -L/usr/local/Trolltech/qwt-6.1.3-qt-4.8.0/arm/lib -lqwt

# for fpga


# for libcpufreq
INCLUDEPATH += /usr/include  #/cpufreq.h
LIBS += -L/usr/lib/ -lcpufreq
#LIBS += -L./lib/arm -lcpufreq



SOURCES += main.cpp\
        blcoremainwindow.cpp \
    cpufreqwidgettab.cpp \
    blcoretabwidget.cpp \
    cpumonitorwidgettab.cpp

HEADERS  += blcoremainwindow.h \
    cpufreqwidgettab.h \
    blcoretabwidget.h \
    cpumonitorwidgettab.h

FORMS    += blcoremainwindow.ui \
    cpufreqwidgettab.ui \
    cpumonitorwidgettab.ui
