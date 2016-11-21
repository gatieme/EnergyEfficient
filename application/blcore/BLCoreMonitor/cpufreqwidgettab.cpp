#include "cpufreqwidgettab.h"
#include "ui_cpufreqwidgettab.h"

CpuFreqWidgetTab::CpuFreqWidgetTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CpuFreqWidgetTab)
{
    ui->setupUi(this);
}

CpuFreqWidgetTab::~CpuFreqWidgetTab()
{
    delete ui;
}
