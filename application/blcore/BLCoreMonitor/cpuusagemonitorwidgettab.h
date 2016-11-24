#ifndef CPUUSAGEMONITORWIDGETTAB_H
#define CPUUSAGEMONITORWIDGETTAB_H

#include <QWidget>
#include <QDebug>
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
class CpuUsageMonitorWidgetTab;
}

class CpuUsageMonitorWidgetTab : public QWidget
{
    Q_OBJECT

public:
    explicit CpuUsageMonitorWidgetTab(QWidget *parent = 0);
    ~CpuUsageMonitorWidgetTab();


public slots:
    void slotShowCpuUsagePlot( );       //  绘制cpu使用率的曲线


private:
    Ui::CpuUsageMonitorWidgetTab *ui;
protected:
    QTimer                  *m_cpuUsageMonitorTimer;        //  cpu频率frequency的监视定时器
    QwtPlotGrid             *m_cpuUsageQwtPlotGrid;
    CpuUtilTools            *m_cpuUtilTools;
};

#endif // CPUUSAGEMONITORWIDGETTAB_H
