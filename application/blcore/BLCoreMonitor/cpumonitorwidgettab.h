#ifndef CPUMONITORWIDGETTAB_H
#define CPUMONITORWIDGETTAB_H

#include <QWidget>

namespace Ui {
class CpuMonitorWidgetTab;
}

class CpuMonitorWidgetTab : public QWidget
{
    Q_OBJECT

public:
    explicit CpuMonitorWidgetTab(QWidget *parent = 0);
    ~CpuMonitorWidgetTab();

private:
    Ui::CpuMonitorWidgetTab *ui;
};

#endif // CPUMONITORWIDGETTAB_H
