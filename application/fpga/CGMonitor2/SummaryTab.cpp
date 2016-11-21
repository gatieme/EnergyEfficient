
#include <QtGui>
#include "SummaryTab.h"
#include "fpgaCGMon.h"
#include "fpga/fpgaCG.h"
#include "IniEx.h"
#include <QDebug>
#include <unistd.h>

void get_cpuoccpy(CPU_OCCUPY * cpust){
    FILE * fd;
    int n;
    char buff[256];
    CPU_OCCUPY * cpu_occupy;
    cpu_occupy=cpust;

    fd = fopen("/proc/stat","r");
    fgets(buff,sizeof(buff),fd);

    sscanf(buff,"%s %u %u %u %u",
           &cpu_occupy->name,
           &cpu_occupy->user,
           &cpu_occupy->nice,
           &cpu_occupy->system,
           &cpu_occupy->idle);

    fclose(fd);


}

int cal_cpuoccupy(CPU_OCCUPY* o, CPU_OCCUPY* n){
    unsigned long od,nd;
    unsigned long id,sd,niced;
    int cpu_use=0;

    od=(unsigned long)(o->user + o->nice + o->system + o->idle);
    nd = (unsigned long)(n->user + n->nice + n->system + n->idle);

    id = (unsigned long)(n->user - o->user);
    sd = (unsigned long)(n->system - o->system);
    niced = (unsigned long)(n->nice - o->nice);

    if((nd-od)!=0)
        //cpu_use = (int)((sd+id+niced))/(nd-od);
        cpu_use = ((float)((nd-od)-(n->idle-o->idle)))/(nd-od)*100;
    else
        cpu_use = 0;
    return cpu_use;

}


QString g_Path;
char FPGAused[100];//每100ms内fpga是否被使用,0--未使用 1--使用中

//! [0]
SummaryTab::SummaryTab(QWidget *parent)
{
    Q_UNUSED(parent);

    descriptionLabel = new QLabel(tr("There are currently no contacts in your address book. "
                                      "\nClick Add to add new contacts."));

    FPGA_used = new QLabel(tr("FPGA使用率"));
    CPU_used = new QLabel(tr("CPU使用率"));
    FPGA_used_percent = new QLabel(tr("0%"));
    CPU_used_percent = new QLabel(tr("0%"));
    m_model_flag=1;
    //进度条
    fpga_used_progress = new QProgressBar();
    cpu_used_progress  = new QProgressBar();
    fpga_used_progress->setOrientation(Qt::Vertical);  //进度条  垂直
    cpu_used_progress->setOrientation(Qt::Vertical);  //进度条  垂直7
    fpga_used_progress->setValue(0);
    cpu_used_progress->setValue(0);

    used_group_box = new QGroupBox(tr("使用率"));

    //FPGA 详细信息组
    IPCorePath = new QLabel(tr ("  IP核路径：     无IP核"));
    SubTypeName = new QLabel(tr("  插入子板类型： 无子板"));
    HandleModel = new QLabel(tr("  处理模式：     正常"));
    Running = new QLabel(tr    ("  FPGA状态：     空闲"));
    FPGA_scription =  new QGroupBox(tr("FPGA详细信息"));
    UtilizationButton = new QPushButton(tr("FPGA资源利用率"));
    connect(UtilizationButton,SIGNAL(clicked()),this,SLOT(slotFPGAUtilization()));

    //设置fpga状态
    setFPGANormal = new QRadioButton(tr("均衡调度"));
    setFPGAForbidden = new QRadioButton(tr("能耗优化"));
    setFPGAMust = new QRadioButton(tr("效率优先"));
    setUseFirst = new QRadioButton(tr("用户选择"));
    setFPGANormal->setChecked(true);
    connect(setFPGANormal,SIGNAL(toggled(bool)),this,SLOT(SlotsetFPGANormal(bool)));
    connect(setFPGAForbidden,SIGNAL(toggled(bool)),this,SLOT(SlotsetFPGAForbidden(bool)));
    connect(setFPGAMust,SIGNAL(toggled(bool)),this,SLOT(SlotsetFPGAForce(bool)));
    connect(setUseFirst,SIGNAL(toggled(bool)),this,SLOT(SlotsetFPGAUseFirst(bool)));


    QSpacerItem* horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* verticalSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* verticalSpacer2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    //QSpacerItem* verticalSpacer3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    //布局
    QHBoxLayout* layout1 = new QHBoxLayout;
    QHBoxLayout* layout2 = new QHBoxLayout;
    QHBoxLayout* layout11 = new QHBoxLayout;
    QVBoxLayout* layout12 = new QVBoxLayout;
    QVBoxLayout* layout13 = new QVBoxLayout;


    QVBoxLayout* layout111 = new QVBoxLayout;
    QVBoxLayout* layout112 = new QVBoxLayout;
    QVBoxLayout* layout131 = new QVBoxLayout;
    QVBoxLayout* layout132 = new QVBoxLayout;

    FPGA_Config =  new QGroupBox(tr("FPGA配置设定"));

    FPGA_Config_Strtegy =  new QGroupBox(tr("数据重构策略"));

    FPGA_support_IOType = new QGroupBox(tr("IO子板自动配置类型"));

    layout111->addWidget(CPU_used_percent);
    layout111->addWidget(cpu_used_progress);
    layout111->addWidget(CPU_used);

    layout112->addWidget(FPGA_used_percent);
    layout112->addWidget(fpga_used_progress);
    layout112->addWidget(FPGA_used);

    layout12->addWidget(IPCorePath);
    layout12->addWidget(SubTypeName);
    layout12->addWidget(HandleModel);
    layout12->addWidget(Running);
    layout12->addWidget(UtilizationButton);


    layout13->addWidget(FPGA_Config_Strtegy);
    layout13->addWidget(FPGA_support_IOType);

    layout131->addWidget(setFPGANormal);
    layout131->addWidget(setFPGAForbidden);
    layout131->addWidget(setFPGAMust);
    layout131->addWidget(setUseFirst);


    subType_RS232 = new QCheckBox(tr("RS232 子板"));
    subType_RS485 = new QCheckBox(tr("RS485 子板"));
    subType_RS422 = new QCheckBox(tr("RS422 子板"));
    subType_CAN = new QCheckBox(tr("CAN 子板"));
    layout132->addWidget(subType_RS232);
    layout132->addWidget(subType_RS422);
    layout132->addWidget(subType_RS485);
    layout132->addWidget(subType_CAN);
    connect(subType_RS232,SIGNAL(clicked(bool)),this,SLOT(slotCheckBoxRS232(bool)));
    connect(subType_RS485,SIGNAL(clicked(bool)),this,SLOT(slotCheckBoxRS485(bool)));
    connect(subType_RS422,SIGNAL(clicked(bool)),this,SLOT(slotCheckBoxRS422(bool)));
    connect(subType_CAN,SIGNAL(clicked(bool)),this,SLOT(slotCheckBoxCAN(bool)));




   // layout11->addWidget(used_group_box);
    FPGA_support_IOType->setLayout(layout132);
    FPGA_Config_Strtegy->setLayout(layout131);

    layout11->addItem(layout111);
    layout11->addItem(layout112);
    used_group_box->setLayout(layout11);
    FPGA_scription->setLayout(layout12);
    FPGA_Config->setLayout(layout13);

    layout1->addWidget(used_group_box);
    layout1->addItem(horizontalSpacer);
    layout1->addWidget(FPGA_scription);
    layout1->addItem(verticalSpacer1);
     layout1->addWidget(FPGA_Config);


    //layout2->addWidget(setFPGANormal);
    //layout2->addWidget(setFPGAForbidden);
    //layout2->addWidget(setFPGAMust);

    mainLayout = new QVBoxLayout;
    mainLayout->addItem(layout1);
    mainLayout->addItem(verticalSpacer2);
    mainLayout->addItem(layout2);
   // mainLayout->addWidget(descriptionLabel);
    //mainLayout->addWidget(used_group_box);

    //连接信号和槽
    setLayout(mainLayout);

    get_cpuoccpy(&old);
    m_oldIOSubType = IO_NULL;
    for(int i=0;i<100;i++)FPGAused[i]=0;
    UpdateData();
    setCGModelSlots(3);
    //打开“重构串口”
// 设置快捷键
    QShortcut *KeyQ = new QShortcut(QKeySequence(Qt::Key_Q),this);
    connect(KeyQ,SIGNAL(activated()),setFPGANormal,SLOT( toggle()));
    QShortcut *KeyW = new QShortcut(QKeySequence(Qt::Key_W),this);
    connect(KeyW,SIGNAL(activated()),setFPGAForbidden,SLOT( toggle()));
    QShortcut *KeyE = new QShortcut(QKeySequence(Qt::Key_E),this);
    connect(KeyE,SIGNAL(activated()),setFPGAMust,SLOT( toggle()));
    QShortcut *KeyR = new QShortcut(QKeySequence(Qt::Key_R),this);
    connect(KeyR,SIGNAL(activated()),setUseFirst,SLOT( toggle()));

    QShortcut *KeyA = new QShortcut(QKeySequence(Qt::Key_A),this);
    connect(KeyA,SIGNAL(activated()),subType_RS232,SLOT( click()));
    QShortcut *Keys = new QShortcut(QKeySequence(Qt::Key_D),this);
    connect(Keys,SIGNAL(activated()),subType_RS485,SLOT( click()));
    QShortcut *KeyD = new QShortcut(QKeySequence(Qt::Key_S),this);
    connect(KeyD,SIGNAL(activated()),subType_RS422,SLOT( click()));
    QShortcut *KeyF = new QShortcut(QKeySequence(Qt::Key_F),this);
    connect(KeyF,SIGNAL(activated()),subType_CAN,SLOT( click()));

    QShortcut *KeyZ = new QShortcut(QKeySequence(Qt::Key_Z),this);
    connect(KeyZ,SIGNAL(activated()),UtilizationButton,SLOT( click()));
}
//! [0]

void SummaryTab:: UpdateData(){

  /*  int FPGAStatusReadIpType();
    int FPGAStatusReadSubType();
    int FPGAStatusReadUsedState();
    int FPGAStatusReadDataControl();
    */

    // IO子板
    int ntype = FPGAStatusReadSubType();
    switch(ntype){
        case IO_RS232:
            setSubcardType("IO_RS232");
            break;
        case IO_RS422:
            setSubcardType("IO_RS422");
            break;
        case IO_RS485:
            setSubcardType("IO_RS485");
            break;
        case IO_CAN:
            setSubcardType("IO_CAN");
            break;
       default:
             setSubcardType("IO_NULL");
            break;

        }


    char subType =  FPGAStatusReadIOControl();
    if(subType>0){
        if((subType&(1<<IO_RS232))==(1<<IO_RS232))
            subType_RS232->setChecked(true);
        else
            subType_RS232->setChecked(false);

        if((subType&(1<<IO_RS485))==(1<<IO_RS485))
            subType_RS485->setChecked(true);
        else
            subType_RS485->setChecked(false);

        if((subType&(1<<IO_RS422))==(1<<IO_RS422))
            subType_RS422->setChecked(true);
        else
            subType_RS422->setChecked(false);

        if((subType&(1<<IO_CAN))==(1<<IO_CAN))
            subType_CAN->setChecked(true);
        else
            subType_CAN->setChecked(false);
    }

    //qDebug()<<"subType: %x"<<(int)subType;
    //支持的IO接口

     //IP核
    ntype = FPGAStatusReadIpType();
    OptName = CGOPFOFindOptNameByIndex(ntype);
    switch(ntype){
        case IPCORE_TYPE_RS232:
        setIPCorePath(IPCORE_PATH_RS232);
        break;

        case IPCORE_TYPE_RS422:
        setIPCorePath(IPCORE_PATH_RS422);
        break;
        case IPCORE_TYPE_RS485:
        setIPCorePath(IPCORE_PATH_RS485);
        break;
        case IPCORE_TYPE_CAN:
        setIPCorePath(IPCORE_PATH_CAN);
        break;
    default:
         setIPCorePath(CGOPFOFindIPCorePathByIndex(ntype));
       // setIPCorePath(tr("/usr/fpga/des.bit"));
        //setIPCorePath(tr("/usr/fpga/jpeg.bit"));
        //setIPCorePath(tr("/usr/fpga/rs232.bit"));
        //setIPCorePath(tr("/usr/fpga/rs422.bit"));
        //setIPCorePath(tr("/usr/fpga/rs485.bit"));
        //setIPCorePath(tr("/usr/fpga/can.bit"));
        //setIPCorePath(tr(""));
        break;

    }

    //处理模式
     ntype = FPGAStatusReadDataControl();
     switch(ntype){
        case 3:
             HandleModel->setText(tr("  处理模式：     用户选择"));
             setUseFirst->setChecked(true);
         break;
         case 2:
             HandleModel->setText(tr("  处理模式：     能耗优化"));
             setFPGAForbidden->setChecked(true);
             break;
         case 1:
             HandleModel->setText(tr("  处理模式：     效率优先"));
             setFPGAMust->setChecked(true);
             break;
         default:
             HandleModel->setText(tr("  处理模式：     均衡调度"));
             setFPGANormal->setChecked(true);
             break;
     }
    // setCGModelSlots(ntype);

     //FPGA状态

      //更新FPGA状态,
      static int nfpgaIndex=0;int usePercentFpga=0;
      for(int i=0;i<10;i++){
          ntype = FPGAStatusReadUsedState();
          setRunningType(ntype);

          switch(ntype){
          case 3://使用中....
              FPGAused[(nfpgaIndex)%100]=1;
              break;
          case 2:// 配置中....
              FPGAused[(nfpgaIndex)%100]=0;
              break;
          case 1://空闲
              FPGAused[(nfpgaIndex)%100]=0;
              break;
          default:
              FPGAused[(nfpgaIndex)%100]=0;
              break;
          }
          nfpgaIndex++;
          if(nfpgaIndex>=100)nfpgaIndex=0;
          usleep(1000*10);
      }

      //更新CPU进度条
      CPU_OCCUPY now1;
      static int ncount=0;
      if(ncount==3){
          get_cpuoccpy(&now1);
          int use = cal_cpuoccupy(&old,&now1);
          setCpuPersent(use);
          old=now1;
          ncount=0;

          //更新FPGAUse进度条
          for(int i=0;i<100;i++) usePercentFpga+=FPGAused[i];
          if(usePercentFpga>=100)
              setFPGAUsePercent(100);
          else if(usePercentFpga<0)
               setFPGAUsePercent(0);
          else
              setFPGAUsePercent(usePercentFpga);
      }else{
           ncount++;
      }



}
void SummaryTab:: ShowIPConfigMessage(QString IPPATH){
    //usleep(1000*1000*5);
    QString mesg;
    mesg.append(tr("正在配置FPGA.....\n"));
    mesg.append(tr("IP核路径：%1\n").arg(IPPATH));
    //mesg.append(tr("IP Path: /usr/fpga/des.bit\n"));
    //mesg.append(tr("IP Path: /usr/fpga/rs232.bit\n"));
    //mesg.append(tr("IP Path: /usr/fpga/rs422.bit\n"));
    //mesg.append(tr("IP Path: /usr/fpga/rs485.bit\n"));
    //mesg.append(tr("IP Path: /usr/fpga/can.bit\n"));
   // mesg.append(tr("\n[3396.261134]cpld open\n start to download full bit file to FPGA\n "));
    //mesg.append(tr("ok,init_b is high\ncpld simulate the CFG wave\n test reg=0x1234 \n"));
    //mesg.append(tr("file download complete45.732%..."));
    //mesg.append(tr("file size=1756643bytes\n1756643 bytes has download!\n"));
   // mesg.append(tr("rd_cnd=1756643\n file download end and check done....\nsucced!\n\n"));
   // mesg.append(tr("....\n IP核配置成功 !!!"));

   // mesg.append(tr("\n\n"));
    g_CCMessage->showText(mesg,5);
}

//槽的实现
void SummaryTab::setCpuPersent(int persent){ //0---100的值，其它值非法
    if(cpu_used_progress !=NULL)
        cpu_used_progress->setValue(persent);
    if(CPU_used_percent !=NULL){
        CPU_used_percent->setText(QString::number(persent,10).append(tr("%")));
    }
    QString mesg;

    if(persent>=70){
    }else if(persent<=30){
        m_model_flag=1;
    }

    if(M_model==0&& m_model_flag==1 && persent>=70){//负载均衡
        mesg.append(tr("任务分配给FPGA处理!\n"));
        g_CCMessage->showText(mesg,5);
        m_model_flag=0;
    }

};
void SummaryTab::setFPGAUsePercent(int persent){//0---100的值，其它值非法
    if(fpga_used_progress !=NULL)
        fpga_used_progress->setValue(persent);
    if(FPGA_used_percent !=NULL){
        FPGA_used_percent->setText(QString::number(persent,10).append(tr("%")));
    }

};
void SummaryTab::setIPCorePath(QString Path){ //Path路径
    if(IPCorePath != NULL){
        IPCorePath->setText(tr("  IP核路径：      ").append(Path));
        m_IPPATH = Path;
    }
}
void SummaryTab::setSubcardType(QString typeName){//子板的名称

    if(SubTypeName != NULL){
        SubTypeName->setText(tr("  插入子板类型： ").append(typeName));
    }
};

void SummaryTab::setRunningType(int typeRunning){ //空闲（1），配置中（2）//，使用中（3）


    if(Running != NULL){
        switch(typeRunning){
        case 3:
            Running->setText(tr("  FPGA状态：     使用中....   "));
            break;
        case 2:
            Running->setText(tr("  FPGA状态：     配置中....   "));
            ShowIPConfigMessage(m_IPPATH);

            break;
        case 1:
            Running->setText(tr("  FPGA状态：     空闲    "));
            break;
        default:
            Running->setText(tr("  FPGA状态：     未初始化    "));
            break;

        }

        //QString mesg = QString(tr("\n\n\n ")) ;
        //mesg.append(tr("CPU使用率低于30%\n\n"));
       // mesg.append(tr("开始任务迁移......\n\n"));
       // mesg.append(tr("迁移成功!!!\n\n"));
       // mesg.append(tr("重构任务由ARM和FPGA共同处理！！\n"));

       // mesg.append(tr("\n\n"));
        //g_CCMessage->showText(mesg,10);

    }
}

void SummaryTab::setCGModelSlots(const int model){ //重构的模式  1---禁止FPGA重构  2--强制FPGA重构，其它--正常模式 3--用户选择

    //设置fpga调度控制字(0--正常，1--强制fpga加速，2--进制fpga加速)
    //客户端可以设置本字段
   // int FPGAStatusWriteDataControl(char control);
    if(HandleModel != NULL){
        switch(model){
        case 3:
            //FPGAStatusWriteDataControl((char)2);
            CGCliSetDataControl(3);
            break;
        case 2:
            //FPGAStatusWriteDataControl((char)2);
            CGCliSetDataControl(2);
            break;
        case 1:
            //FPGAStatusWriteDataControl(1);
            CGCliSetDataControl(1);
            break;
        default:
            //FPGAStatusWriteDataControl(0);
             CGCliSetDataControl(0);
            break;

        }
        M_model=model;

    }
}

void SummaryTab::SlotsetFPGANormal(bool checked){
    if(checked){
        setCGModelSlots(0);
    }

}

void SummaryTab::SlotsetFPGAForbidden(bool checked){
    if(checked){
        setCGModelSlots(2);
    }

}

void SummaryTab::SlotsetFPGAForce(bool checked){
    if(checked){
        setCGModelSlots(1);
    }

}
void SummaryTab::SlotsetFPGAUseFirst(bool checked){
    if(checked){
       setCGModelSlots(3);
    }

}

void SummaryTab::slotFPGAUtilization(){


    UtilizationDialog* dialog = new UtilizationDialog(this,OptName);
    dialog->show();
}

void SummaryTab::slotCheckBoxRS232(bool state){

    if(state==true){
        CGCliSetSubID(IO_RS232,1);
         //CGIOSetSubType(m_fd,IO_RS232,1);
    }else{
         CGCliSetSubID(IO_RS232,0);
        // CGIOSetSubType(m_fd,IO_RS232,0);
    }
}

void SummaryTab::slotCheckBoxRS422(bool state){
    if(state==true){
         CGCliSetSubID(IO_RS422,1);
        // CGIOSetSubType(m_fd,IO_RS422,1);
    }else{
         CGCliSetSubID(IO_RS422,0);
         //CGIOSetSubType(m_fd,IO_RS422,0);
    }

}

void SummaryTab::slotCheckBoxRS485(bool state){

    if(state==true){
        CGCliSetSubID(IO_RS485,1);
         //CGIOSetSubType(m_fd,IO_RS485,1);
    }else{
         CGCliSetSubID(IO_RS485,0);
         //CGIOSetSubType(m_fd,IO_RS485,0);
    }
}

void SummaryTab::slotCheckBoxCAN(bool state){

    if(state==true){
        CGCliSetSubID(IO_CAN,1);
        // CGIOSetSubType(m_fd,IO_CAN,1);
    }else{
        CGCliSetSubID(IO_CAN,0);
         //CGIOSetSubType(m_fd,IO_CAN,0);
    }
}




UtilizationDialog::UtilizationDialog(QWidget *parent,QString opt){



    //a[10]={10,45,34,34,12,45,67,86,34,67};

//从文件读取数值
    CIniEx1 IniEx;
    a[0]=IniEx.GetIntValue(opt,"Registers",0);
    a[1]=IniEx.GetIntValue(opt,"LUTs",0);
    a[2]=IniEx.GetIntValue(opt,"Logic",0);
    a[3]=IniEx.GetIntValue(opt,"Memory",0);
    a[4]=IniEx.GetIntValue(opt,"Slices",0);
    a[5]=IniEx.GetIntValue(opt,"LUT-FF_pairs",0);
    a[6]=IniEx.GetIntValue(opt,"Bonded_IOBs",0);
    a[7]=IniEx.GetIntValue(opt,"BlockRAM",0);
    a[8]=IniEx.GetIntValue(opt,"TotalMemoryUsed",0);
    a[9]=IniEx.GetIntValue(opt,"BUFGCTRLs",0);


    Init();

    this->setWindowTitle(tr("FPGA资源利用率--").append(opt));
    QShortcut *quitKey = new QShortcut(QKeySequence(Qt::Key_Escape),this);
    connect(quitKey,SIGNAL(activated()),this,SLOT(close()));

}

void UtilizationDialog::Init(){


    //显示界面
        exitButton=NULL;
        register_progress = new QProgressBar();
        LUTs_progress  = new QProgressBar();
        Logic_progress = new QProgressBar();
        Memory_progress  = new QProgressBar();
        Slices_progress = new QProgressBar();
        LUT_FF_pairs_progress  = new QProgressBar();
        Bonded_IOBs_progress = new QProgressBar();
        BlockRam_FIFO_progress  = new QProgressBar();
        Total_Memory_progress = new QProgressBar();
        BUFG_BUFGCTRLs_progress  = new QProgressBar();



        register_progress->setOrientation(Qt::Vertical);  //进度条  垂直
        LUTs_progress->setOrientation(Qt::Vertical);  //进度条  垂直
        Logic_progress->setOrientation(Qt::Vertical);  //进度条  垂直
        Memory_progress->setOrientation(Qt::Vertical);  //进度条  垂直
        Slices_progress->setOrientation(Qt::Vertical);  //进度条  垂直
        LUT_FF_pairs_progress->setOrientation(Qt::Vertical);  //进度条  垂直
        Bonded_IOBs_progress->setOrientation(Qt::Vertical);  //进度条  垂直
        BlockRam_FIFO_progress->setOrientation(Qt::Vertical);  //进度条  垂直
        Total_Memory_progress->setOrientation(Qt::Vertical);  //进度条  垂直
        BUFG_BUFGCTRLs_progress->setOrientation(Qt::Vertical);  //进度条  垂直

        register_progress->setTextVisible(true);



        register_progress->setValue(a[0]);
        LUTs_progress->setValue(a[1]);
        Logic_progress->setValue(a[2]);
        Memory_progress->setValue(a[3]);
        Slices_progress->setValue(a[4]);
        LUT_FF_pairs_progress->setValue(a[5]);
        Bonded_IOBs_progress->setValue(a[6]);
        BlockRam_FIFO_progress->setValue(a[7]);
        Total_Memory_progress->setValue(a[8]);
        BUFG_BUFGCTRLs_progress->setValue(a[9]);


        Label1 = new QLabel(tr ("Registers"));
        Label2 = new QLabel(tr ("LUTs"));
        Label3 =new QLabel(tr ("Logic"));
        Label4 =new QLabel(tr ("Memory"));
        Label5 =new QLabel(tr ("Occupied Slices"));
        Label6 =new QLabel(tr ("LUT-FF Pairs"));
        Label7 =new QLabel(tr ("Bonded IOBs"));
        Label8 =new QLabel(tr ("BlockRAM/FIFO"));
        Label9 =new QLabel(tr ("Total Memory Used(KB)"));
        Label10 =new QLabel(tr ("BUFG/BUFGCTRLs"));

        Label11=new QLabel(tr ("%1%").arg(a[0]));
        Label21=new QLabel(tr ("%1%").arg(a[1]));;
        Label31=new QLabel(tr ("%1%").arg(a[2]));;
        Label41=new QLabel(tr ("%1%").arg(a[3]));;
        Label51=new QLabel(tr ("%1%").arg(a[4]));;
        Label61=new QLabel(tr ("%1%").arg(a[5]));;
        Label71=new QLabel(tr ("%1%").arg(a[6]));;
        Label81=new QLabel(tr ("%1%").arg(a[7]));;
        Label91=new QLabel(tr ("%1%").arg(a[8]));;
        Label101=new QLabel(tr ("%1%").arg(a[9]));;



        layout = new QGridLayout(this);
        layout->addWidget(Label11,0,1);
        layout->addWidget(Label21,0,2);
        layout->addWidget(Label31,0,3);
        layout->addWidget(Label41,0,4);
        layout->addWidget(Label51,0,5);
        layout->addWidget(register_progress,1,1);
        layout->addWidget(LUTs_progress,1,2);
        layout->addWidget(Logic_progress,1,3);
        layout->addWidget(Memory_progress,1,4);
        layout->addWidget(Slices_progress,1,5);
        layout->addWidget(Label1,2,1);
        layout->addWidget(Label2,2,2);
        layout->addWidget(Label3,2,3);
        layout->addWidget(Label4,2,4);
        layout->addWidget(Label5,2,5);

        layout->addWidget(Label61,3,1);
        layout->addWidget(Label71,3,2);
        layout->addWidget(Label81,3,3);
        layout->addWidget(Label91,3,4);
        layout->addWidget(Label101,3,5);
        layout->addWidget(LUT_FF_pairs_progress,4,1);
        layout->addWidget(Bonded_IOBs_progress,4,2);
        layout->addWidget(BlockRam_FIFO_progress,4,3);
        layout->addWidget(Total_Memory_progress,4,4);
        layout->addWidget(BUFG_BUFGCTRLs_progress,4,5);
        layout->addWidget(Label6,5,1);
        layout->addWidget(Label7,5,2);
        layout->addWidget(Label8,5,3);
        layout->addWidget(Label9,5,4);
        layout->addWidget(Label10,5,5);

        setLayout(layout);

}

void UtilizationDialog::SetData(){


    register_progress->setValue(a[0]);
    LUTs_progress->setValue(a[1]);
    Logic_progress->setValue(a[2]);
    Memory_progress->setValue(a[3]);
    Slices_progress->setValue(a[4]);
    LUT_FF_pairs_progress->setValue(a[5]);
    Bonded_IOBs_progress->setValue(a[6]);
    BlockRam_FIFO_progress->setValue(a[7]);
    Total_Memory_progress->setValue(a[8]);
    BUFG_BUFGCTRLs_progress->setValue(a[9]);

}

UtilizationDialog::~UtilizationDialog(){


    delete register_progress;
    delete LUTs_progress;
    delete Logic_progress;
    delete Memory_progress;
    delete LUT_FF_pairs_progress;
    delete Slices_progress;
    delete Bonded_IOBs_progress;
    delete BlockRam_FIFO_progress;
    delete Total_Memory_progress;
    delete BUFG_BUFGCTRLs_progress;
    delete Label1;
    delete Label2;
    delete Label3;
    delete Label4;
    delete Label5;
    delete Label6;
    delete Label7;
    delete Label8;
    delete Label9;
    delete Label10;
    delete exitButton;
    delete layout;

    delete Label11;
    delete Label21;
    delete Label21;
    delete Label41;
    delete Label51;
    delete Label61;
    delete Label71;
    delete Label81;
    delete Label91;
    delete Label101;


}

