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
    this->ui->cpuUsageQwtPlot->setAxisTitle(QwtPlot::xBottom, "Time");
    this->ui->cpuUsageQwtPlot->setAxisScale(QwtPlot::xBottom, 0, 10);
    // 增加网格
    this->m_cpuUsageQwtPlotGrid = new QwtPlotGrid();
    this->m_cpuUsageQwtPlotGrid->attach( this->ui->cpuUsageQwtPlot);

    //QwtLegend *legend = new QwtLegend;
    //legend->setDefaultItemMode( QwtLegendData::Checkable );
    //this->ui->cpuUsageQwtPlot->insertLegend( legend, QwtPlot::RightLegend );
    this->ui->cpuUsageQwtPlot->insertLegend( new QwtLegend(), QwtPlot::RightLegend );

    // 设置画布背景
    this->ui->cpuUsageQwtPlot->setCanvasBackground(QColor(29, 100, 141)); // nice blue
    //qDebug( ) <<this->m_cpunums <<endl;
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
    //qDebug( ) <<this->m_cpuUsageQwtPlotCurves.length( ) <<endl;

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
        //qDebug( ) <<this->m_cpuUsageQwtPlotCurves.length( ) <<endl;
        foreach (QwtPlotCurve *curve, this->m_cpuUsageQwtPlotCurves)
        {
            delete curve;
        }
    }
    this->m_cpuUsageQwtPlotCurves.clear( );
}



QwtPlotCurve*   CpuUsageMonitorWidgetTab::InitCpuUsageQwtPlotCurve(unsigned int cpuid)
{
    QString curveName;
    if(cpuid < this->m_cpunums)
    {
        curveName = QString("cpu" +  QString::number((int)cpuid));
    }
    else
    {
        curveName = "cpu";
    }
    QwtPlotCurve* cpuUsgaeCurve = new QwtPlotCurve(curveName);
    cpuUsgaeCurve->setLegendAttribute( QwtPlotCurve::LegendShowLine, true );
    cpuUsgaeCurve->setSamples(this->m_cpuusagesX, this->m_cpuusagesY[cpuid]);
    cpuUsgaeCurve->attach( this->ui->cpuUsageQwtPlot);
//        cpuUsgaeCurve->setStyle( QwtPlotCurve::NoCurve );
    cpuUsgaeCurve->setSymbol( new QwtSymbol( QwtSymbol::XCross,
                    Qt::NoBrush, this->SetCpuUsageQwtPlotPen(cpuid),
                    QSize(QWT_PLOT_POINT_WIDTH, QWT_PLOT_POINT_WIDTH ) ) );
    //  设置曲线颜色
    cpuUsgaeCurve->setPen(this->SetCpuUsageQwtPlotPen(cpuid));

    //  抗锯齿
    //cpuUsgaeCurve->setRenderHint(QwtPlotItem::RenderAntialiased,true);
    cpuUsgaeCurve->setCurveAttribute(QwtPlotCurve::Fitted, true);

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
    //double maxY = 100;
    this->ui->cpuUsageQwtPlot->setAxisScale(QwtPlot::xBottom, 0, maxX);
    //this->ui->cpuUsageQwtPlot->setAxisScale(QwtPlot::yLeft, 0, maxY);

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
    }
    this->ui->cpuUsageQwtPlot->replot( );

}


QPen CpuUsageMonitorWidgetTab::SetCpuUsageQwtPlotPen(unsigned int cpuid)
{
    /*
     * 赤色【RGB】255, 0, 0 【CMYK】 0, 100, 100, 0
     * 橙色【RGB】 255, 165, 0 【CMYK】0, 35, 100, 0
     * 黄色【RGB】255, 255, 0 【CMYK】0, 0, 100, 0
     * 绿色【RGB】0, 255, 0 【CMYK】100, 0, 100, 0
     * 青色【RGB】0, 127, 255 【CMYK】100, 50, 0, 0
     * 蓝色【RGB】0, 0, 255 【CMYK】100, 100, 0, 0
     * 紫色【RGB】139, 0, 255 【CMYK】45, 100, 0, 0
     */
    QVector<QPen> pens = {
        QPen(Qt::red, QWT_PLOT_CURVE_WIDTH),
        QPen(Qt::green, QWT_PLOT_CURVE_WIDTH),
        QPen(Qt::yellow, QWT_PLOT_CURVE_WIDTH),
        QPen(Qt::cyan, QWT_PLOT_CURVE_WIDTH),
        QPen(Qt::magenta, QWT_PLOT_CURVE_WIDTH),
        QPen(Qt::blue, QWT_PLOT_CURVE_WIDTH),
        QPen(Qt::gray, QWT_PLOT_CURVE_WIDTH)
                         };

    return pens[cpuid];
}

void CpuUsageMonitorWidgetTab::UpdateAllCpusUsageData()
{
    //  更新当前cpu的usage信息
    QList<double> usages = this->m_cpuUtilTools->UpdateAllCpusUsage( );
    //  维护最大的cpu频率值, 用以设置Y轴的坐标
    //double maxUsage = *std::max_element(usages.constBegin(), usages.constEnd());


    //  将获取到的新的cpuusage信息添加到数据集合m_cpuusagesX和m_cpuusagesY中
    for(unsigned int cpuid = 0;
        cpuid <= this->m_cpunums;  /* 每个CPU的使用率 +　总的系统使用率*/
        cpuid++)
    {
        qDebug() <<"CPU" <<cpuid <<", USAGE = " <<usages[cpuid];
        //  QVector<double> m_cpuusagesY[cpuid]中存储了编号为cpuid的cpu的usgae信息集合
        //  double usgaes[cpuid] 存储了获取到的编号为cpuid的cpu的usgae最新的信息
        this->m_cpuusagesY[cpuid].append(usages[cpuid]);
    }
    this->m_cpuusagesX.append(this->m_cpuusagesX.size( ));

#ifdef __DEBUG__
    for(unsigned int num = 0;
        num < this->m_cpuusagesX.size( );
        num++)
    {
        qDebug( ) <<"X = " <<this->m_cpuusagesX[num] <<", Y = " <<this->m_cpuusagesY[0][num];
    }
#endif

}
