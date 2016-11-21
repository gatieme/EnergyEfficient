
#include <QtGui>
#include "MonitorWidget.h"
#include "ccmessage.h"
#include "fpga/fpgaCG.h"
CCMessage* g_CCMessage;
static MonitorWidget* g_MonitorWidget;

//! [0]
MonitorWidget::MonitorWidget(QWidget *parent)
    : QTabWidget(parent)
{


    g_MonitorWidget = this;
    g_CCMessage = new CCMessage(this);

    summaryTab = new SummaryTab(this);
    finshedTab = new FinshedTaskTab(this);
    HistoryTab = new HistorySummaryTab(this);
    OnGoingTab = new OngoingTaskTab(this);

    supportTab = new SupportedOptTab(this);
    IOTab = new IOModuleTab(this);

    addTab(summaryTab, tr("重构状态信息"));
    addTab(finshedTab, tr("最近完成任务"));
    addTab(HistoryTab, tr("历史统计"));
    addTab(IOTab, tr("IO模块"));
    addTab(OnGoingTab, tr("正在处理任务"));
    addTab(supportTab, tr("支持操作链表"));

    m_timer = new QTimer();
    m_timer->setInterval(1000);
    m_timer->start();

    connect(m_timer,SIGNAL(timeout()),this,SLOT(onTimerOut()));

    QShortcut *key1 = new QShortcut(QKeySequence(Qt::Key_F12),this);
    connect(key1,SIGNAL(activated()),this,SLOT(Add10LittleFuzai()));
    QShortcut *key2 = new QShortcut(QKeySequence(Qt::Key_F11),this);
    connect(key2,SIGNAL(activated()),this,SLOT(Add1LargeFuzai()));

}
//! [0]

void MonitorWidget::onTimerOut(){
    summaryTab->UpdateData();
    OnGoingTab->UpdateData();
    finshedTab->UpdateData();
    HistoryTab->UpdateData();
}


void MonitorWidget::hideNow(){

    g_CCMessage->hideNow();
}

void MonitorWidget::ShowSum(){
    this->showPage(summaryTab);
}
void MonitorWidget::ShowHistory(){
    this->showPage(HistoryTab);

}
void MonitorWidget::ShowOngoing(){
this->showPage(OnGoingTab);
}
void MonitorWidget::showSupport(){
    this->showPage(supportTab);
}
void MonitorWidget::showFinished(){
    this->showPage(finshedTab);
}

void MonitorWidget::Add10LittleFuzai(){
    int i=0;
    int isFPGA = 1;
    for(i=0;i<10;i++){
        isFPGA=i%2;
        DESEncryptionFileAsyn((unsigned char*)"/usr/cc/1K.txt",isFPGA,NULL,NULL);
    }
    QString mesg;
    mesg.append(tr("向重构服务请求%1项DES加密计算任务........\n").arg(i));
    g_CCMessage->showText(mesg,3);
}
void MonitorWidget::Add1LargeFuzai(){


    int isFPGA = rand()%2;
    DESEncryptionFileAsyn((unsigned char*)"/usr/cc/1M.txt",isFPGA,NULL,NULL);

    QString mesg;
    mesg.append(tr("向重构服务请求一项DES加密计算任务........\n"));
    g_CCMessage->showText(mesg,3);
}
void CCMessage::hideNow(){

    this->hide();
    this->m_timer->stop();
}

CCMessage::CCMessage(QWidget *parent) :
    QMainWindow(parent)
{
    this->setCaption(tr("信息"));
    m_label = new QLabel(tr (""));
    m_label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    m_timer = new QTimer();
    connect(m_timer,SIGNAL(timeout()),g_MonitorWidget,SLOT(hideNow()));
    this->setCentralWidget(m_label);
    this->setFixedWidth(600);
    this->hide();
    this->move((QApplication::desktop()->width()-this->width())/2,
               (QApplication::desktop()->height()-this->height())/2);
}


void CCMessage::showText(QString string, int second ){
    if(second>=0){
        m_label->setText(string);
        m_timer->setInterval(1000*second);
        m_timer->start();
    }else{
         m_label->setText(string);

    }

    this->show();
}

void CCMessage::changeText(QString newstring){
    m_label->setText(newstring);
}
