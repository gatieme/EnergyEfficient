#ifndef BLCORETABWIDGET_H
#define BLCORETABWIDGET_H

#include <QTabWidget>
#include "blcoretabwidget.h"


#include "cpumonitorwidgettab.h"    //  CPU监控子系统
#include "cpufreqwidgettab.h"       //  COU变频调节子系统


class BLCoreTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit BLCoreTabWidget(QWidget *parent = 0);
    virtual ~BLCoreTabWidget();

signals:

public slots:


protected   :
    CpuMonitorWidgetTab *m_cpumonitorWidgetTab;     //  CPU监控子系统
    CpuFreqWidgetTab    *m_cpufreqWidgetTab;        //  CPU变频子系统

};

#endif // BLCORETABWIDGET_H
