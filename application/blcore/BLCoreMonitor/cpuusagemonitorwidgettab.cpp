#include "cpuusagemonitorwidgettab.h"
#include "ui_cpuusagemonitorwidgettab.h"

CpuUsageMonitorWidgetTab::CpuUsageMonitorWidgetTab(QWidget *parent, unsigned int cpunums) :
    QWidget(parent), m_cpunums(cpunums),
    ui(new Ui::CpuUsageMonitorWidgetTab)
{
    ui->setupUi(this);

    ///////////////////////////////////
    ///  初始化调频工具类
    ///////////////////////////////////
    this->m_cpuUtilTools = CpuUtilTools::GetInstance( );
    if(this->m_cpunums == (unsigned int)-1)
    {
        this->m_cpunums = this->m_cpuUtilTools->GetCpuNumKernel( );
    }
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
    this->ui->cpuUsageQwtPlot->setAxisScale(QwtPlot::xBottom, 0, 10);
    // 增加网格
    this->m_cpuUsageQwtPlotGrid = new QwtPlotGrid();
    this->m_cpuUsageQwtPlotGrid->attach( this->ui->cpuUsageQwtPlot);

    // 设置画布背景
    this->ui->cpuUsageQwtPlot->setCanvasBackground(QColor(29, 100, 141)); // nice blue
    qDebug( ) <<this->m_cpunums <<endl;
    for(unsigned int cpuid  = 0;
        cpuid <= this->m_cpunums;  /* 每个CPU的使用率 +　总的系统使用率*/
        cpuid++)
    {
        /////////////////////
        /// 设置CPU USAGE的usage集合信息
        /////////////////////
        /// 未使用指针, 可能会有问题
        QVector<double> cpuusageY;
        this->m_cpuusagesY.append(cpuusageY);

        /////////////////////
        /// 设置CPU USAGE的曲线信息
        /////////////////////
        //新建一个曲线对象
        QwtPlotCurve *cpuUsgaeCurve = this->InitCpuUsageQwtPlotCurve(cpuid);

        //  将曲线对象添加到CPU USAGE曲线集合中
        this->m_cpuUsageQwtPlotCurves.append(cpuUsgaeCurve);
    }


    // panning with the left mouse button支持鼠标平移
    ( void ) new QwtPlotPanner( this->ui->cpuUsageQwtPlot->canvas() );

    // zoom in/out with the wheel支持滚轮放大缩小
    ( void ) new QwtPlotMagnifier( this->ui->cpuUsageQwtPlot->canvas() );




}




CpuUsageMonitorWidgetTab::~CpuUsageMonitorWidgetTab()
{
    delete ui;
    delete m_cpuUsageQwtPlotGrid;
    delete m_cpuUsageMonitorTimer;
    if(this->m_cpuUsageQwtPlotCurves.size( ) != 0)
    {
        foreach (QwtPlotCurve *curve, this->m_cpuUsageQwtPlotCurves)
        {
            delete curve;
        }
    }
    this->m_cpuUsageQwtPlotCurves.clear( );
}



QwtPlotCurve*   CpuUsageMonitorWidgetTab::InitCpuUsageQwtPlotCurve(unsigned int cpuid)
{
    QwtPlotCurve* cpuUsgaeCurve = new QwtPlotCurve("cpu" + cpuid);
    cpuUsgaeCurve->setSamples(this->m_cpuusagesX, this->m_cpuusagesY[cpuid]);
    cpuUsgaeCurve->attach( this->ui->cpuUsageQwtPlot);
//        cpuUsgaeCurve->setStyle( QwtPlotCurve::NoCurve );
    cpuUsgaeCurve->setSymbol( new QwtSymbol( QwtSymbol::XCross,
                    Qt::NoBrush, QPen( Qt::red ), QSize(5, 5 ) ) );
    //  设置曲线颜色
    QPen pen;   //  未使用指针, 可能会有问题
    pen.setColor(QColor(cpuid * 10 + 200, cpuid * 50, cpuid * 10));
    cpuUsgaeCurve->setPen(pen);
    //  抗锯齿
    cpuUsgaeCurve->setRenderHint(QwtPlotItem::RenderAntialiased,true);

    return cpuUsgaeCurve;
}

//  绘制cpu使用率的曲线
void CpuUsageMonitorWidgetTab::slotShowCpuUsagePlot()
{
    this->UpdateAllCpusUsageData( );            //  更新cpuusage的信息
    this->UpdateCpuUsagePlot( );
}

void CpuUsageMonitorWidgetTab::UpdateCpuUsagePlot()
{
    double maxX = (this->m_cpuusagesX.size( ) > 10) ? (double)this->m_cpuusagesX.size( ) : 10;
    double maxY = 20;
    this->ui->cpuUsageQwtPlot->setAxisScale(QwtPlot::xBottom, 0, maxX);
    this->ui->cpuUsageQwtPlot->setAxisScale(QwtPlot::yLeft, 0, maxY);

    for(unsigned int cpuid  = 0;
        cpuid <= this->m_cpunums;  /* 每个CPU的使用率 +　总的系统使用率*/
        cpuid++)
    {
        /////////////////////
        /// 设置CPU USAGE的曲线信息
        /////////////////////
        //新建一个曲线对象
        QwtPlotCurve *cpuUsgaeCurve = this->m_cpuUsageQwtPlotCurves[cpuid];
        cpuUsgaeCurve->setSamples(this->m_cpuusagesX, this->m_cpuusagesY[cpuid]);
        cpuUsgaeCurve->attach( this->ui->cpuUsageQwtPlot);


        //  抗锯齿
        cpuUsgaeCurve->setRenderHint(QwtPlotItem::RenderAntialiased,true);

        //  将曲线对象添加到CPU USAGE曲线集合中
        this->m_cpuUsageQwtPlotCurves.append(cpuUsgaeCurve);
    }
    this->ui->cpuUsageQwtPlot->replot( );

}

void CpuUsageMonitorWidgetTab::UpdateAllCpusUsageData()
{
    //  更新当前cpu的usage信息
    QList<double> usages = this->m_cpuUtilTools->UpdateAllCpusUsage( );
    //  维护最大的cpu频率值, 用以设置Y轴的坐标
    for(unsigned int cpuid = 0;
        cpuid <= this->m_cpunums;  /* 每个CPU的使用率 +　总的系统使用率*/
        cpuid++)
    {
        //  QVector<double> m_cpuusagesY[cpuid]中存储了编号为cpuid的cpu的usgae信息集合
        //  double usgaes[cpuid] 存储了获取到的编号为cpuid的cpu的usgae最新的信息
        this->m_cpuusagesY[cpuid].append(usages[cpuid]);
    }
    this->m_cpuusagesX.append(this->m_cpuusagesX.size( ) + 1);

    for(unsigned int num = 0;
        num < this->m_cpuusagesX.size( );
        num++)
    {
        qDebug( ) <<"X = " <<this->m_cpuusagesX[num] <<", Y = " <<this->m_cpuusagesY[0][num];
    }

}
