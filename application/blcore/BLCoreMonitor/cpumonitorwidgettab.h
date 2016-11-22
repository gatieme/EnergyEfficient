#ifndef CPUMONITORWIDGETTAB_H
#define CPUMONITORWIDGETTAB_H

#include <QWidget>

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



namespace Ui {
class CpuMonitorWidgetTab;
}

class CpuMonitorWidgetTab : public QWidget
{
    Q_OBJECT

public:
    explicit CpuMonitorWidgetTab(QWidget *parent = 0);
    ~CpuMonitorWidgetTab();

private slots:
    void slotShowCpuUsagePlot( );       //  绘制cpu使用率的曲线
    void slotShowCpuUsageFrequency( );  //  绘制cpu频率的曲线

private:
    Ui::CpuMonitorWidgetTab *ui;

protected :


    QwtPlotGrid     *m_cpuUsageQwtPlotGrid;
    QwtPlotGrid     *m_cpuFrequencyQwtPlotGrid;


};

#endif // CPUMONITORWIDGETTAB_H
