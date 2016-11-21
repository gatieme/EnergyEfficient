
#include <QtGui>
#include "HistorySummaryTab.h"
#include "fpgaCGMon.h"

static HistorySummaryTab* g_taskTab;
static int g_index;
static void VisitPrintf(struct SummaryItem* pArmItem,struct SummaryItem* pFPGAItem){


    if(pArmItem ==NULL || pFPGAItem==NULL || g_taskTab==NULL) return;

    if(g_index== g_taskTab->m_index)
         g_taskTab->SetPaint(pArmItem,pFPGAItem);

    g_index++;

}

//! [0]
HistorySummaryTab::HistorySummaryTab(QWidget *parent)
{
    Q_UNUSED(parent);

    descriptionLabel = new QLabel(tr("There are currently no contacts in your address book. "
                                    "\nClick Add to add new contacts."));

    QPalette bgpalRed = palette();
    bgpalRed.setColor (QPalette::Background, QColor (255, 0 , 0, 255));
    QPalette bgpalBlue = palette();
    bgpalBlue.setColor (QPalette::Background, QColor (0, 0 , 255, 255));
    QPalette bgpalGreen = palette();
    bgpalGreen.setColor (QPalette::Background, QColor (0, 255 , 0, 255));


    descriptionLabel->setPalette(bgpalRed);
    descriptionLabel->setAutoFillBackground(true);

    //汇总信息的group边框
    Totalgroup=new QGroupBox(tr("汇总信息"));
    timeTotalArm=new QLabel(tr("0"));
    timeTotalFPGA=new QLabel(tr("0"));
    sizeTotalArm=new QLabel(tr("0"));
    sizeTotalFPGA=new QLabel(tr("0"));

    NumTotalArm=new QLabel(tr("0"));
    NumTotalFPGA=new QLabel(tr("0"));

    textTotalArm=new QLabel(tr("时间 "));
    textTotalFPGA=new QLabel(tr("大小 "));
    textTotalNum=new QLabel(tr("任务数 "));
    textARM=new QLabel(tr("ARM "));
    textFPGA=new QLabel(tr("FPGA "));
    totalTimeNumber=new QLabel(tr("总耗时： 0  ms"));
    totalSizeNumber=new QLabel(tr("总大小： 0  bytes"));
    totalNumNumber=new QLabel(tr("总任务数: 0  个"));

    //设置颜色，大小，下沉
    timeTotalArm->setPalette(bgpalRed);
    timeTotalArm->setAutoFillBackground(true);
    timeTotalFPGA->setPalette(bgpalBlue);
    timeTotalFPGA->setAutoFillBackground(true);
    sizeTotalArm->setPalette(bgpalRed);
    sizeTotalArm->setAutoFillBackground(true);
    sizeTotalFPGA->setPalette(bgpalBlue);
    sizeTotalFPGA->setAutoFillBackground(true);
    NumTotalArm->setPalette(bgpalRed);
    NumTotalArm->setAutoFillBackground(true);

    NumTotalFPGA->setPalette(bgpalBlue);
    NumTotalFPGA->setAutoFillBackground(true);

    textARM->setPalette(bgpalRed);
    textARM->setAutoFillBackground(true);
    textFPGA->setPalette(bgpalBlue);
    textFPGA->setAutoFillBackground(true);


    timeTotalArm->setFrameShadow ( QFrame::Sunken );
    timeTotalFPGA->setFrameShadow ( QFrame::Sunken );

    textARM->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    textFPGA->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    timeTotalArm->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    timeTotalFPGA->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    sizeTotalArm->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    sizeTotalFPGA->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    NumTotalArm->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    NumTotalFPGA->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    textTotalArm->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    textTotalFPGA->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    timeTotalArm->setFixedSize(50,200);
    timeTotalFPGA->setFixedSize(50,200);
    NumTotalArm->setFixedSize(50,200);
    NumTotalFPGA->setFixedSize(50,200);
    sizeTotalArm->setFixedSize(50,200);
    sizeTotalFPGA->setFixedSize(50,200);
    //调整大小无效？
    timeTotalArm->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Preferred);
    NumTotalFPGA->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Preferred);
    NumTotalArm->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Preferred);
    timeTotalFPGA->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Preferred);
    textTotalArm->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);


    //布局
    QHBoxLayout* layout1 = new QHBoxLayout;
    QVBoxLayout* layout11 = new QVBoxLayout;
    QVBoxLayout* layout12 = new QVBoxLayout;
    QVBoxLayout* layout13 = new QVBoxLayout;
    QVBoxLayout* layout14 = new QVBoxLayout;

    layout1->setSizeConstraint(QLayout::SetNoConstraint);


    layout1->addStretch(1);
    layout1->addItem(layout11);
    layout1->addStretch(1);
    layout1->addItem(layout12);
    layout1->addStretch(1);
    layout1->addItem(layout14);
    layout1->addStretch(2);
    layout1->addItem(layout13);
    layout1->addStretch(1);


    layout11->addStretch(1);
    layout11->addWidget(timeTotalArm);
    layout11->addWidget(timeTotalFPGA);
    layout11->addWidget(textTotalArm);
    layout11->addStretch(1);

    layout12->addStretch(1);
    layout12->addWidget(sizeTotalArm);
    layout12->addWidget(sizeTotalFPGA);
    layout12->addWidget(textTotalFPGA);
    layout12->addStretch(1);


    layout14->addStretch(1);
    layout14->addWidget(NumTotalArm);
    layout14->addWidget(NumTotalFPGA);
    layout14->addWidget(textTotalNum);
    layout14->addStretch(1);

    layout13->addStretch(1);
    layout13->addWidget(textARM);
    layout13->addWidget(textFPGA);
    layout13->addWidget(totalSizeNumber);
    layout13->addWidget(totalTimeNumber);
    layout13->addWidget(totalNumNumber);
    layout13->addStretch(3);

    Totalgroup->setLayout(layout1);



    QVBoxLayout* layout1Button = new QVBoxLayout;
    m_button1=new QPushButton(tr("汇总"));
    m_button2=new QPushButton(tr("JPEG"));
    m_button3=new QPushButton(tr("DES"));
    layout1Button->addWidget(m_button1);
    layout1Button->addWidget(m_button2);
    layout1Button->addWidget(m_button3);

    connect(m_button1,SIGNAL(clicked()),this,SLOT(slotButton1()));
    connect(m_button2,SIGNAL(clicked()),this,SLOT(slotButton2()));
    connect(m_button3,SIGNAL(clicked()),this,SLOT(slotButton3()));


    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(Totalgroup);
    mainLayout->addLayout(layout1Button);
    setLayout(mainLayout);

     m_index=0;


    /*************/
    g_taskTab=this;
    UpdateData();
    //PrintfCHST();
    printf("\n");

    //设置快捷键
    QShortcut *Key_1 = new QShortcut(QKeySequence(Qt::Key_H),this);
    connect(Key_1,SIGNAL(activated()),this,SLOT(slotButton1()));

    QShortcut *Key_5 = new QShortcut(QKeySequence(Qt::Key_J),this);
    connect(Key_5,SIGNAL(activated()),this,SLOT(slotButton2()));

    QShortcut *Key_2 = new QShortcut(QKeySequence(Qt::Key_D),this);
    connect(Key_2,SIGNAL(activated()),this,SLOT(slotButton3()));

}
//! [0]


 void HistorySummaryTab::UpdateData(){

    g_index=0;
    CGHSTTraverse(VisitPrintf);

   // g_taskTab->SetPaint(pArmItem,pFPGAItem);

 }

//设置显示画面
void HistorySummaryTab::SetPaint(struct SummaryItem* pArmItem,struct SummaryItem* pFPGAItem){

    if(pArmItem==NULL || pFPGAItem==NULL) return;


    //名字
    if(m_index ==0){ //汇总信息
        Totalgroup->setTitle(tr("汇总信息"));
    }else{
         Totalgroup->setTitle((char*)pointerConverter(pArmItem->optname));
    }

    //时间
    totalTimeNumber->setText(tr("总耗时： %1  ms").arg(pArmItem->time+pFPGAItem->time));
    timeTotalArm->setText(tr("%1").arg(pArmItem->time));
    timeTotalFPGA->setText(tr("%1").arg(pFPGAItem->time));
    if(pArmItem->time+pFPGAItem->time ==0){
        timeTotalArm->setFixedSize(50,200);
        timeTotalFPGA->setFixedSize(50,200);

    }else{

        int lenFpgaTime =400*(((pFPGAItem->time)*1.0)/((pArmItem->time+pFPGAItem->time)*1.0));
        int lenArmTime = 400-lenFpgaTime;
        timeTotalArm->setFixedSize(50,lenArmTime);
        timeTotalFPGA->setFixedSize(50,lenFpgaTime);

    }


    //大小
    totalSizeNumber->setText(tr("总大小： %1  bytes").arg(pArmItem->sourbytesize+pFPGAItem->sourbytesize));
    sizeTotalArm->setText(tr("%1").arg(pArmItem->sourbytesize));
    sizeTotalFPGA->setText(tr("%1").arg(pFPGAItem->sourbytesize));
    if(pArmItem->sourbytesize+pFPGAItem->sourbytesize ==0){
        sizeTotalArm->setFixedSize(50,200);
        sizeTotalFPGA->setFixedSize(50,200);

    }else{
        int lenArmTime = 400*((pArmItem->sourbytesize)*1.0)/((pArmItem->sourbytesize+pFPGAItem->sourbytesize)*1.0);
        int lenFpgaTime =400-lenArmTime;
        sizeTotalArm->setFixedSize(50,lenArmTime);
        sizeTotalFPGA->setFixedSize(50,lenFpgaTime);
    }

    //任务数
    totalNumNumber->setText(tr("总任务数 %1  个").arg(pArmItem->num+pFPGAItem->num));
    NumTotalArm->setText(tr("%1").arg(pArmItem->num));
    NumTotalFPGA->setText(tr("%1").arg(pFPGAItem->num));
    if(pArmItem->num+pFPGAItem->num ==0){
        NumTotalArm->setFixedSize(50,200);
        NumTotalFPGA->setFixedSize(50,200);

    }else{
        int lenArmTime = 400*((pArmItem->num)*1.0)/((pArmItem->num+pFPGAItem->num)*1.0);
        int lenFpgaTime =400-lenArmTime;
        NumTotalArm->setFixedSize(50,lenArmTime);
        NumTotalFPGA->setFixedSize(50,lenFpgaTime);
    }



}

void HistorySummaryTab::slotButton1(){
    m_index=0;

    UpdateData();

}


void HistorySummaryTab::slotButton2(){
    m_index=1;

    UpdateData();

}

void HistorySummaryTab::slotButton3(){
    m_index=2;

    UpdateData();

}
