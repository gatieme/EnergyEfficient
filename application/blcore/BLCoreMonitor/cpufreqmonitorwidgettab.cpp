#include "cpufreqmonitorwidgettab.h"
#include "ui_cpufreqmonitorwidgettab.h"

CpuFreqMonitorWidgetTab::CpuFreqMonitorWidgetTab(QWidget *parent, unsigned int cpunums) :
    QWidget(parent), m_cpunums(cpunums),
    ui(new Ui::CpuFreqMonitorWidgetTab)
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
    this->m_cpufreqMonitorTimer = new QTimer(this);
    connect(this->m_cpufreqMonitorTimer, SIGNAL(timeout( )),
            this, SLOT(slotShowCpuFrequencyPlot( )));
    this->m_cpufreqMonitorTimer->start(1000);

    ///////////////////////////////////
    /// CPU频率图表cpuFreqQwtPlot
    ///////////////////////////////////
    //  设置其Y轴信息
    this->ui->cpuFrequencyQwtPlot->setAxisTitle(QwtPlot::yLeft, "Frequency(kHZ)" );
    this->ui->cpuFrequencyQwtPlot->setAxisScale(QwtPlot::yLeft,
                                                this->m_cpuUtilTools->GetScalingMinFrequency(0),
                                                this->m_cpuUtilTools->GetScalingMaxFrequency(0));
    this->ui->cpuFrequencyQwtPlot->setAxisTitle(QwtPlot::xBottom, "Time");
    this->ui->cpuFrequencyQwtPlot->setAxisScale(QwtPlot::xBottom, 0, 10);
    this->ui->cpuFrequencyQwtPlot->insertLegend( new QwtLegend(), QwtPlot::RightLegend );

    // 增加网格
    this->m_cpufreqQwtPlotGrid = new QwtPlotGrid();
    this->m_cpufreqQwtPlotGrid->attach( this->ui->cpuFrequencyQwtPlot);


    // 设置画布背景
    this->ui->cpuFrequencyQwtPlot->setCanvasBackground(QColor(29, 100, 141)); // nice blue
    //qDebug( ) <<this->m_cpunums <<endl;
    for(unsigned int cpuid  = 0;
        cpuid < this->m_cpunums;  /* 每个CPU的使用率  */
        cpuid++)
    {
        /////////////////////
        /// 设置CPU Freq集合信息
        /////////////////////
        QVector<double> cpuufreqY;
        this->m_cpufreqsY.append(cpuufreqY);

        /////////////////////
        /// 设置CPU USAGE的曲线信息
        /////////////////////
        //新建一个曲线对象
        QwtPlotCurve *cpuFrequencyCurve = this->InitCpuFrequencyQwtPlotCurve(cpuid);

        //  将曲线对象添加到CPU USAGE曲线集合中
        this->m_cpufreqQwtPlotCurves.append(cpuFrequencyCurve);
    }
    //qDebug( ) <<this->m_cpuFreqQwtPlotCurves.length( ) <<endl;

    // panning with the left mouse button支持鼠标平移
    ( void ) new QwtPlotPanner( this->ui->cpuFrequencyQwtPlot->canvas() );

    // zoom in/out with the wheel支持滚轮放大缩小
    ( void ) new QwtPlotMagnifier( this->ui->cpuFrequencyQwtPlot->canvas() );
}




CpuFreqMonitorWidgetTab::~CpuFreqMonitorWidgetTab()
{
    delete ui;
    delete m_cpufreqQwtPlotGrid;
    delete m_cpufreqMonitorTimer;
    if(this->m_cpufreqQwtPlotCurves.size( ) != 0)
    {
        //qDebug( ) <<this->m_cpuFreqQwtPlotCurves.length( ) <<endl;
        foreach (QwtPlotCurve *curve, this->m_cpufreqQwtPlotCurves)
        {
            delete curve;
        }
    }
    this->m_cpufreqQwtPlotCurves.clear( );
}



QwtPlotCurve*   CpuFreqMonitorWidgetTab::InitCpuFrequencyQwtPlotCurve(unsigned int cpuid)
{
    QString curveName = QString("cpu" +  QString::number((int)cpuid));
    QwtPlotCurve* cpuFrequencyCurve = new QwtPlotCurve(curveName);
    cpuFrequencyCurve->setLegendAttribute( QwtPlotCurve::LegendShowLine, true );
    cpuFrequencyCurve->setSamples(this->m_cpufreqsX, this->m_cpufreqsY[cpuid]);
    cpuFrequencyCurve->attach( this->ui->cpuFrequencyQwtPlot);
//        cpuFrequencyCurve->setStyle( QwtPlotCurve::NoCurve );
    cpuFrequencyCurve->setSymbol( new QwtSymbol( QwtSymbol::XCross,
                    Qt::NoBrush, this->SetCpuFrequencyQwtPlotPen(cpuid),
                    QSize(QWT_PLOT_POINT_WIDTH, QWT_PLOT_POINT_WIDTH ) ) );
    //  设置曲线颜色
    cpuFrequencyCurve->setPen(this->SetCpuFrequencyQwtPlotPen(cpuid));

    //  抗锯齿
    //cpuFrequencyCurve->setRenderHint(QwtPlotItem::RenderAntialiased,true);
    cpuFrequencyCurve->setCurveAttribute(QwtPlotCurve::Fitted, true);

    return cpuFrequencyCurve;
}

//  绘制cpu使用率的曲线
void CpuFreqMonitorWidgetTab::slotShowCpuFrequencyPlot()
{
    this->UpdateAllCpusFrequencyData( );            //  更新cpuusage的信息
    this->UpdateCpuFrequencyPlot( );
}

void CpuFreqMonitorWidgetTab::UpdateCpuFrequencyPlot()
{

    double  maxX = (this->m_cpufreqsX.size( ) > 10) ? (double)this->m_cpufreqsX.size( ) : 10;
    //double maxY = 100;
    this->ui->cpuFrequencyQwtPlot->setAxisScale(QwtPlot::xBottom, 0, maxX);
    //this->ui->cpuFreqQwtPlot->setAxisScale(QwtPlot::yLeft, 0, maxY);

    for(unsigned int cpuid  = 0;
        cpuid < this->m_cpunums;  /* 每个CPU的使用率 +　总的系统使用率*/
        cpuid++)
    {
        /////////////////////
        /// 设置CPU USAGE的曲线信息
        /////////////////////
        //新建一个曲线对象
        QwtPlotCurve *cpuFrequencyCurve = this->m_cpufreqQwtPlotCurves[cpuid];
        cpuFrequencyCurve->setSamples(this->m_cpufreqsX, this->m_cpufreqsY[cpuid]);
    }
    this->ui->cpuFrequencyQwtPlot->replot( );

}


QPen CpuFreqMonitorWidgetTab::SetCpuFrequencyQwtPlotPen(unsigned int cpuid)
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

void CpuFreqMonitorWidgetTab::UpdateAllCpusFrequencyData()
{
    //  更新当前cpu的usage信息
    QList<double> frequencys = this->m_cpuUtilTools->UpdateAllCpusScalingCurFrequency( );
    //  维护最大的cpu频率值, 用以设置Y轴的坐标
    //double maxUsage = *std::max_element(frequencys.constBegin(), frequencys.constEnd());


    //  将获取到的新的cpuusage信息添加到数据集合m_cpufrequencysX和m_cpufrequencysY中
    for(unsigned int cpuid = 0;
        cpuid < this->m_cpunums;  /* 每个CPU的使用率 +　总的系统使用率*/
        cpuid++)
    {
        //  QVector<double> m_cpufrequencysY[cpuid]中存储了编号为cpuid的cpu的usgae信息集合
        //  double usgaes[cpuid] 存储了获取到的编号为cpuid的cpu的usgae最新的信息
        qDebug() <<"CPU" <<cpuid <<", FREQ = " <<frequencys[cpuid];
        this->m_cpufreqsY[cpuid].append(frequencys[cpuid]);
    }
    this->m_cpufreqsX.append(this->m_cpufreqsX.size( ));

}


