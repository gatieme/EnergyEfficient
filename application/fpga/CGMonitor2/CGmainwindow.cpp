#include <QtGui>
#include "CGmainwindow.h"
#include "fpga/fpgaCG.h"
#include<signal.h>
//#include "fpgaCG-SupportedOpt.h"


CGMainWindow::CGMainWindow()
{
    //1.Init
    CGCliInit();

    monitorWidget = new MonitorWidget;
    setCentralWidget(monitorWidget);

    signal(SIGPIPE, SIG_IGN);
    setWindowTitle(tr("动态可重构任务管理器"));

 /* SummaryTab *summaryTab;
    FinshedTaskTab *finshedTab;
    HistorySummaryTab *HistoryTab;
    IOModuleTab *IOTab;
    OngoingTaskTab *OnGoingTab;
    SupportedOptTab* supportTab;void ShowHistory();
    void ShowOngoing();
    void showSupport();
*/
    QShortcut *quitKey = new QShortcut(QKeySequence(Qt::Key_Escape),this);
    connect(quitKey,SIGNAL(activated()),this,SLOT(close()));

    QShortcut *Key_1 = new QShortcut(QKeySequence(Qt::Key_1),this);
    connect(Key_1,SIGNAL(activated()),monitorWidget,SLOT(ShowSum()));

    QShortcut *Key_5 = new QShortcut(QKeySequence(Qt::Key_2),this);
    connect(Key_5,SIGNAL(activated()),monitorWidget,SLOT(showFinished()));


    QShortcut *Key_2 = new QShortcut(QKeySequence(Qt::Key_4),this);
    connect(Key_2,SIGNAL(activated()),monitorWidget,SLOT(ShowOngoing()));

    QShortcut *Key_3 = new QShortcut(QKeySequence(Qt::Key_3),this);
    connect(Key_3,SIGNAL(activated()),monitorWidget,SLOT(ShowHistory()));

    QShortcut *Key_4 = new QShortcut(QKeySequence(Qt::Key_5),this);
    connect(Key_4,SIGNAL(activated()),monitorWidget,SLOT(showSupport()));


    this-> showNormal();
}

void CGMainWindow::showDes(){
    if(des != NULL){
        des->show();
        des->move(400,50);
    }
}
void CGMainWindow::showJpeg(){
    if(jpeg != NULL){
        jpeg->show();
        jpeg->move(400,50);
    }
}
void CGMainWindow::SetQuickShort(){
    QShortcut *Key_F1 = new QShortcut(QKeySequence(Qt::Key_F1),this);
    connect(Key_F1,SIGNAL(activated()),this,SLOT(showDes()));

    QShortcut *Key_F2 = new QShortcut(QKeySequence(Qt::Key_F2),this);
    connect(Key_F2,SIGNAL(activated()),this,SLOT(showJpeg()));


}
