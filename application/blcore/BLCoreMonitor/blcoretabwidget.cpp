#include "blcoretabwidget.h"

BLCoreTabWidget::BLCoreTabWidget(QWidget *parent) :
    QTabWidget(parent)
{

    //  变频子窗体CpuFreqWidgetTab的添加
    this->m_cpufreqWidgetTab  = new CpuFreqWidgetTab(this);
    this->addTab(this->m_cpufreqWidgetTab, tr("变频"));

    //  tiao
    this->m_cpufreqMonitorWidgetTab = new CpuFreqMonitorWidgetTab(this);
    this->addTab(this->m_cpufreqMonitorWidgetTab, tr("监控"));

    //
    this->m_cpuusageMonitorWidgetTab = new CpuUsageMonitorWidgetTab(this);
    this->addTab(this->m_cpuusageMonitorWidgetTab, tr("使用率"));
}


BLCoreTabWidget::~BLCoreTabWidget( )
{
    delete m_cpufreqWidgetTab;
    delete m_cpufreqMonitorWidgetTab;
    delete m_cpuusageMonitorWidgetTab;
}
