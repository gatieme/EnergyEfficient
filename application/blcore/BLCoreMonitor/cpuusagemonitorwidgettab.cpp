#include "cpuusagemonitorwidgettab.h"
#include "ui_cpuusagemonitorwidgettab.h"

CpuUsageMonitorWidgetTab::CpuUsageMonitorWidgetTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CpuUsageMonitorWidgetTab)
{
    ui->setupUi(this);

    ///////////////////////////////////
    ///  初始化调频工具类
    ///////////////////////////////////
    this->m_cpuUtilTools = CpuUtilTools::GetInstance( );

    ///////////////////////////////////
    /// 定时器每隔一秒中开始读取cpufreq的信息
    /// QTimer *m_cpuUsageMonitorTimer      cpu频率frequency的监视定时器
    /// QTimer *m_cpuFrequencyMonitorTimer  cpu使用率usage的监视定时器
    ///////////////////////////////////
    this->m_cpuUsageMonitorTimer = new QTimer(this);
    connect(this->m_cpuUsageMonitorTimer, SIGNAL(timeout( )),
            this, SLOT(slotShowCpuUsagePlot( )));
    this->m_cpuUsageMonitorTimer->start(1000);





    ///////////////////////////////////
    /// CPU使用率图表cpuUsageQwtPlot
    ///////////////////////////////////
    //  设置其Y轴信息
    this->ui->cpuUsageQwtPlot->setAxisTitle(QwtPlot::yLeft, "Usage(%)" );
    this->ui->cpuUsageQwtPlot->setAxisScale(QwtPlot::yLeft, 0, 100);
    // 增加网格
    this->m_cpuUsageQwtPlotGrid = new QwtPlotGrid();
    this->m_cpuUsageQwtPlotGrid->attach( this->ui->cpuUsageQwtPlot);
    // 设置画布背景
    this->ui->cpuUsageQwtPlot->setCanvasBackground(QColor(29, 100, 141)); // nice blue
    /*
    // panning with the left mouse button支持鼠标平移
    ( void ) new QwtPlotPanner( this->ui->cpuUsageQwtPlot->canvas() );

    // zoom in/out with the wheel支持滚轮放大缩小
    ( void ) new QwtPlotMagnifier( this->ui->cpuUsageQwtPlot->canvas() );
    */

    /*
    //新建一个曲线对象
    //tPlotCurve *pCurve=new QwtPlotCurve("route");
     this->m_locateCurve->setSamples(xData, yData);
     this->m_locateCurve->attach( this->ui->plotLocate);

     this->m_locateCurve->setStyle( QwtPlotCurve::NoCurve );
     this->m_locateCurve->setSymbol( new QwtSymbol( QwtSymbol::XCross,
        Qt::NoBrush, QPen( Qt::red ), QSize(5, 5 ) ) );
     //设置曲线颜色
     QPen pen;
     pen.setColor(QColor(255,0,0));

      this->m_locateCurve->setPen(pen);


    //抗锯齿
    this->m_locateCurve->setRenderHint(QwtPlotItem::RenderAntialiased,true);
    */


}

CpuUsageMonitorWidgetTab::~CpuUsageMonitorWidgetTab()
{
    delete ui;
}


//  绘制cpu使用率的曲线
void CpuUsageMonitorWidgetTab::slotShowCpuUsagePlot()
{
    this->m_cpuUtilTools->UpdateAllCpusUsage( );
    //qDebug( ) <<__FILE__ <<", " <<__LINE__ <<endl;

}
