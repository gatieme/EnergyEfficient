#ifndef BLCOREMAINWINDOW_H
#define BLCOREMAINWINDOW_H

#include <QMainWindow>

#include "blcoretabwidget.h"    // tabwidget
#include "cpufrequtils.h"       //  cpu调频工具类

namespace Ui {
class BLCoreMainWindow;
}

class BLCoreMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BLCoreMainWindow(QWidget *parent = 0);
    ~BLCoreMainWindow();

private:
    Ui::BLCoreMainWindow *ui;

protected :

    CpuFreqUtils    *m_cpuFreqUtils;            //  CPU调频工具类
    //  注意m_cpuFreqUtils必须优先于窗体完成初始化, 并被所有窗体共享

    BLCoreTabWidget *m_blcoreTabWidget;         //  tabwidget
};

#endif // BLCOREMAINWINDOW_H
