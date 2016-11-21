
#include <QtGui>
#include "SupportedOptTab.h"

//! [0]

static QList<struct CGOptBaseInfo*> g_allSupportOpt;//支持操作表全局
static void VisitPrintf(struct CGOptBaseInfo* task){


    if(task ==NULL) return;

      g_allSupportOpt.push_back(task);

};


SupportedOptTab::SupportedOptTab(QWidget *parent)
{
    Q_UNUSED(parent);



   /* QPushButton* leftButton = new QPushButton("<");
    QPushButton* rightButton = new QPushButton(">");

    leftButton->setFixedWidth(50);
    leftButton->setFixedHeight(parent->size().height());
    rightButton->setFixedWidth(50);
    rightButton->setFixedHeight(parent->size().height());
*/
     /***************初始化布局**********************/
    //重构操作的标签项
    cliOptSOPath = new QLabel(tr("cliOptSOPath:                              "));
    srvOPtSOPath = new QLabel(tr("srvOptSOPath:                              "));
    ipCorePath = new QLabel(tr("ipCorePath:                                  "));
    InitTime = new QLabel(tr("InitTime:                                      "));
    cliFuncName = new QLabel(tr("cliFuncName:                                "));
    srvARMFuncName = new QLabel(tr("srvARMFuncName:                          "));
    srvFPGAFuncName = new QLabel(tr("srvFPGAFuncName:                        "));
    descriptionLabel = new QLabel(tr("descriptionLabel:  \n 好厉害的样子\n\n\n\n\n\n"));
    timeLabel = new QLabel();

    operationDescriptionGroup = new QGroupBox(tr("重构操作名"));
    operationDescriptionGroup->setAlignment(Qt::AlignHCenter );

    QVBoxLayout* optLayout = new QVBoxLayout;
    optLayout->addWidget(InitTime);
    optLayout->addWidget(cliFuncName);
    optLayout->addWidget(srvARMFuncName);
    optLayout->addWidget(srvFPGAFuncName);
    optLayout->addWidget(cliOptSOPath);
    optLayout->addWidget(srvOPtSOPath);
    optLayout->addWidget(ipCorePath);
    optLayout->addWidget(descriptionLabel);
    optLayout->addWidget(timeLabel);
    operationDescriptionGroup->setLayout(optLayout);





    /***************初始化数据**********************/
    CGSOTraverse(VisitPrintf);

    if(!g_allSupportOpt.isEmpty()){
        struct CGOptBaseInfo* pOptBase = g_allSupportOpt.at(0);
        QPushButton* leftButton = new QPushButton(pOptBase->OptName);
        connect(leftButton,SIGNAL(clicked()),this,SLOT(SlotSupportButton1()));


        pOptBase = g_allSupportOpt.at(1);
        QPushButton* rightButton = new QPushButton(pOptBase->OptName);
        connect(rightButton,SIGNAL(clicked()),this,SLOT(SlotSupportButton2()));


        //布局
        QSpacerItem* verticalSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        QSpacerItem* verticalSpacer2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        hLayout = new QVBoxLayout;

        hLayout->addItem(verticalSpacer1);
        hLayout->addWidget(operationDescriptionGroup);
        hLayout->addItem(verticalSpacer2);
        hLayout->addWidget(rightButton);
        hLayout->addWidget(leftButton);
        setLayout(hLayout);
        showUpOpt(g_allSupportOpt.at(0));

    }

   // PrintfSOT();


    /***********************/



}

void SupportedOptTab::SlotSupportButton1(){

    showUpOpt(g_allSupportOpt.at(0));
}

void SupportedOptTab::SlotSupportButton2(){

    showUpOpt(g_allSupportOpt.at(1));
}




SupportedOptTab::~SupportedOptTab(){

    /*if(mainLayout!=NULL) delete  mainLayout;
    if(hLayout!=NULL) delete hLayout;
    if(leftButton!=NULL) delete leftButton;

    if(rightButton!=NULL) delete  rightButton;
    if(operationDescriptionGroup!=NULL) delete operationDescriptionGroup;
    if(cliOptSOPath!=NULL) delete cliOptSOPath;

    if(srvOPtSOPath!=NULL) delete  srvOPtSOPath;
    if(ipCorePath!=NULL) delete ipCorePath;
    if(InitTime!=NULL) delete InitTime;

    if(cliFuncName!=NULL) delete  cliFuncName;
    if(srvARMFuncName!=NULL) delete srvARMFuncName;
    if(srvFPGAFuncName!=NULL) delete srvFPGAFuncName;

    if(descriptionLabel!=NULL) delete  descriptionLabel;
    if(timeLabel!=NULL) delete timeLabel;
    */


}
 void SupportedOptTab::showUpOpt(struct CGOptBaseInfo* pBasInfo){
     if(pBasInfo ==NULL) return;

     operationDescriptionGroup->setTitle(pBasInfo->OptName);

     cliOptSOPath->setText(    tr("客户端库文件:     %1").arg(pBasInfo->CliOptSoPath));
     srvOPtSOPath->setText(    tr("服务端库文件:     %1").arg(pBasInfo->SrvOptSoPath));
     ipCorePath->setText(      tr("IP核路径:        %1").arg(pBasInfo->IpCorePath));
     InitTime->setText(        tr("初始化时间:       %1  ms").arg(pBasInfo->InitTime));
     cliFuncName->setText(     tr("客户端函数名:     %1").arg(pBasInfo->CliFuncName));
     srvARMFuncName->setText(  tr("服务端ARM函数名:  %1").arg(pBasInfo->SrvArmFuncName));
     srvFPGAFuncName->setText( tr("服务端FPGA函数名: %1").arg(pBasInfo->SrvFPGAFuncName));
     descriptionLabel->setText(tr("功能描述:\n %1\n").arg(pBasInfo->Describe));

     //显示时间标签
     QString qtemp(tr("-----------     -处理数据时间---------------\n"));
     qtemp.append("| DataLen(%d)  | ArmTime(%d) | FPGATime(%d)|\n");



     struct CGOptTime* ptime=(pBasInfo->time);
     while(ptime!=NULL){

        ptime =  (struct CGOptTime*)pointerConverter(ptime);
         qtemp.append(tr("| %1 Byte|  %2 ms|  %3 ms|\n").arg(QString::number(ptime->datasize),
                                 QString::number(ptime->armtime),
                                 QString::number(ptime->fpgatime)));
         ptime = ptime->pNext;
     }

     timeLabel->setText(qtemp);

 }
//! [0]


