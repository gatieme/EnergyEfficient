#include "cpumonitorwidgettab.h"
#include "ui_cpumonitorwidgettab.h"

CpuMonitorWidgetTab::CpuMonitorWidgetTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CpuMonitorWidgetTab)
{
    ui->setupUi(this);
}

CpuMonitorWidgetTab::~CpuMonitorWidgetTab()
{
    delete ui;
}
