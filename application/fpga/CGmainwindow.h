#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "fpga/CGMonitor2/MonitorWidget.h"
#include "fpga/des/DESmainwindow.h"
#include "fpga/jpeg/JPEGmainwindow.h"

//! [0]
class CGMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CGMainWindow();
    DESMainWindow* des;
    JPEGMainWindow* jpeg;

    void SetQuickShort();
private slots:
    void showDes();
    void showJpeg();
private:
    MonitorWidget* monitorWidget;

};
//! [0]

#endif

