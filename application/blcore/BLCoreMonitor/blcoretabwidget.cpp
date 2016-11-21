#include "blcoretabwidget.h"

BLCoreTabWidget::BLCoreTabWidget(QWidget *parent) :
    QTabWidget(parent)
{


    //
    this->m_cpumonitorWidgetTab = new CpuMonitorWidgetTab(this);
    this->addTab(m_cpumonitorWidgetTab, tr("监控"));
    //  变频子窗体CpuFreqWidgetTab的添加
    this->m_cpufreqWidgetTab  = new CpuFreqWidgetTab(this);
    this->addTab(m_cpufreqWidgetTab, tr("变频"));
}


BLCoreTabWidget::~BLCoreTabWidget( )
{
    delete m_cpumonitorWidgetTab;
    delete m_cpufreqWidgetTab;

}
