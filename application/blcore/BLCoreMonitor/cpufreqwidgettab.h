#ifndef CPUFREQWIDGETTAB_H
#define CPUFREQWIDGETTAB_H

#include <QWidget>

#include "cpufrequtils.h"

namespace Ui{
class CpuFreqWidgetTab;
}

class CpuFreqWidgetTab : public QWidget
{
    Q_OBJECT

public:
    explicit CpuFreqWidgetTab(QWidget *parent = 0);
    ~CpuFreqWidgetTab();



private:
    Ui::CpuFreqWidgetTab   *ui;
};

#endif // CPUFREQWIDGETTAB_H
