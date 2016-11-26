#ifndef CPUUSAGEMONITORWIDGETTAB_H
#define CPUUSAGEMONITORWIDGETTAB_H

#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <QVector>

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
    explicit CpuUsageMonitorWidgetTab(QWidget *parent = 0, unsigned int cpunums = -1);
    ~CpuUsageMonitorWidgetTab();
    QwtPlotCurve*   InitCpuUsageQwtPlotCurve(unsigned int cpuid);


public slots:
    void slotShowCpuUsagePlot( );       //  绘制cpu使用率的曲线
    void UpdateCpuUsagePlot( );       //  绘制cpu使用率的曲线
    void UpdateAllCpusUsageData();

private:
    Ui::CpuUsageMonitorWidgetTab *ui;
protected:
    unsigned int            m_cpunums;
    CpuUtilTools            *m_cpuUtilTools;
    QTimer                  *m_cpuUsageMonitorTimer;        //  cpu频率frequency的监视定时器


    QwtPlotGrid             *m_cpuUsageQwtPlotGrid;         //  qwt的网格
    QList<QVector<double>>  m_cpuusagesY;                    //  m_cpuusages[cpuid]存储着编号为cpuid的cpu的usage信息
    QVector<double>         m_cpuusagesX;                    //  x轴的信息, 时间
    //QwtPlotDirectPainter    *m_cpuUsageQwtPlotPainter;               // 增量绘图工具
    QList<QwtPlotCurve *>   m_cpuUsageQwtPlotCurves;         // 定位曲线对象
    //QList<QPen *>           m_cpuUsagePen;                  // QPen
    //QwtPlotMarker         *m_locateLocalMarker;       //  路线起点标记
    //LocateMarkerList      m_locateMarkerList;     // 定位信息

    ///  保护函数 辅助功能
//    inline double GetMaxCpuUsageData( )
//    {
//        return 0;
//    }
//    inline double GetMinCpuUsageData( );
    QPen SetCpuUsageQwtPlotPen(unsigned int cpuid);
};

#endif // CPUUSAGEMONITORWIDGETTAB_H
