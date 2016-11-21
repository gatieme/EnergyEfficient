#include "blcoremainwindow.h"
#include "ui_blcoremainwindow.h"


BLCoreMainWindow::BLCoreMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BLCoreMainWindow)
{
    ui->setupUi(this);


    //  工具栏, 菜单栏和状态栏的隐藏
    this->ui->mainToolBar->hide( );     //  隐藏工具栏
    this->ui->menuBar->hide();          //  隐藏菜单栏
    this->ui->statusBar->hide( );       //  隐藏状态栏

    //  添加tabwidget
    m_blcoreTabWidget= new BLCoreTabWidget();
    setCentralWidget(m_blcoreTabWidget);

    //signal(SIGPIPE, SIG_IGN);
    setWindowTitle(tr("多核低功耗调度平台"));
}

BLCoreMainWindow::~BLCoreMainWindow()
{
    delete ui;
}
