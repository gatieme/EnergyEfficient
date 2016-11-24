#ifndef BLCORETABWIDGET_H
#define BLCORETABWIDGET_H

#include <QTabWidget>
#include "blcoretabwidget.h"


#include "cpufreqmonitorwidgettab.h"    //  CPU监控子系统
#include "cpufreqwidgettab.h"       //  COU变频调节子系统
#include "cpuusagemonitorwidgettab.h"   //  CPU使用率监控子系统

class BLCoreTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit BLCoreTabWidget(QWidget *parent = 0);
    virtual ~BLCoreTabWidget();

signals:

public slots:


protected   :
    CpuFreqMonitorWidgetTab     *m_cpufreqMonitorWidgetTab;     //  CPU监控子系统
    CpuFreqWidgetTab            *m_cpufreqWidgetTab;        //  CPU变频子系统
    CpuUsageMonitorWidgetTab    *m_cpuusageMonitorWidgetTab;
};

#endif // BLCORETABWIDGET_H
