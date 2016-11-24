#ifndef CPUMONITORWIDGETTAB_H
#define CPUMONITORWIDGETTAB_H

#include <QWidget>
#include <QTimer>



/// qwt-6.1.3
#include <qwt_plot.h>
#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_point_data.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_text.h>
#include <qwt_symbol.h>
#include <qwt_math.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_directpainter.h>

#include "cpuutiltools.h"


namespace Ui {
class CpuFreqMonitorWidgetTab;
}

class CpuFreqMonitorWidgetTab : public QWidget
{
    Q_OBJECT

public:
    explicit CpuFreqMonitorWidgetTab(QWidget *parent = 0);
    ~CpuFreqMonitorWidgetTab();

private slots:

    void slotShowCpuFrequencyPlot( );  //  绘制cpu频率的曲线

private:
    Ui::CpuFreqMonitorWidgetTab *ui;

protected :


    QwtPlotGrid     *m_cpuFrequencyQwtPlotGrid;
    QTimer          *m_cpuFrequencyMonitorTimer;    //  cpu使用率usage的监视定时器

    CpuUtilTools    *m_cpuUtilTools;                //  CPU调频工具类
    //  注意m_cpuFreqUtils必须优先于窗体完成初始化, 并被所有窗体共享


};

#endif // CPUMONITORWIDGETTAB_H
