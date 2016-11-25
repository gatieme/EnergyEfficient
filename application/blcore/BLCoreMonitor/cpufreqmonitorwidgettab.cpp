#include "cpufreqmonitorwidgettab.h"
#include "ui_cpufreqmonitorwidgettab.h"

CpuFreqMonitorWidgetTab::CpuFreqMonitorWidgetTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CpuFreqMonitorWidgetTab)
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
    this->m_cpuFrequencyMonitorTimer = new QTimer(this);
    connect(this->m_cpuFrequencyMonitorTimer, SIGNAL(timeout( )),
            this, SLOT(slotShowCpuFrequencyPlot( )));
    this->m_cpuFrequencyMonitorTimer->start(1000);




    ///////////////////////////////////
    /// CPU频率的图表cpuFrequencyQwtPlot
    ///////////////////////////////////
    //  CPU频率的图, 设置其Ｙ轴信息
    this->ui->cpuFrequencyQwtPlot->setAxisTitle(QwtPlot::yLeft, "Frequency(MHZ)" );
    this->ui->cpuFrequencyQwtPlot->setAxisScale(QwtPlot::yLeft, 800, 3000);
    // 增加网格
    this->m_cpuFrequencyQwtPlotGrid = new QwtPlotGrid();
    this->m_cpuFrequencyQwtPlotGrid->attach(this->ui->cpuFrequencyQwtPlot);
    // 设置画布背景
    this->ui->cpuFrequencyQwtPlot->setCanvasBackground(QColor(29, 100, 141)); // nice blue
    /*
    // panning with the left mouse button支持鼠标平移
    ( void ) new QwtPlotPanner( this->ui->cpuFrequencyQwtPlot->canvas() );

    // zoom in/out with the wheel支持滚轮放大缩小
    ( void ) new QwtPlotMagnifier( this->ui->cpuFrequencyQwtPlot->canvas() );
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


CpuFreqMonitorWidgetTab::~CpuFreqMonitorWidgetTab()
{
    delete ui;
}



//  绘制cpu频率的曲线
void CpuFreqMonitorWidgetTab::slotShowCpuFrequencyPlot( )
{
    this->m_cpuUtilTools->UpdateAllCpusScalingCurFrequency( );

    //qDebug( ) <<__FILE__ <<", " <<__LINE__ <<endl;
}

