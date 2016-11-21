
#include <QtGui>
#include "FinishedTaskTab.h"
#include "fpgaCGMon.h"

static FinshedTaskTab* g_taskTab;
static int g_index;
static void VisitPrintf(struct FinishedTask* task){


    if(task ==NULL) return;

     g_taskTab->InserOngingtToList(task,g_index++);

}

void FinshedTaskTab::InserOngingtToList(struct FinishedTask* pTask,int row){
    if(pTask==NULL || row<0) return;

    this->student_model->setItem(row,0,new QStandardItem(tr("%1").arg(pTask->index)));
    this->student_model->setItem(row,1,new QStandardItem(CGOPFOFindOptNameByIndex(pTask->optType)));
    //this->student_model->setItem(row,2,new QStandardItem((pTask->ArmOrFPGA==1)?"ARM":"FPGA"));
    this->student_model->setItem(row,2,new QStandardItem((pTask->ArmOrFPGA==1)?"ARM":((pTask->ArmOrFPGA==2)?"FPGA":((pTask->ArmOrFPGA==3)?"ARM+FPGA":"Mix"))));
    this->student_model->setItem(row,3,new QStandardItem(tr("%1").arg(pTask->UsedTime)));
    this->student_model->setItem(row,4,new QStandardItem(tr("%1").arg(pTask->Cli_pid)));
    this->student_model->setItem(row,5,new QStandardItem(tr("%1").arg(pTask->sourMemSize)));
    this->student_model->setItem(row,6,new QStandardItem(tr("%1").arg(pTask->tarMemSize)));
}

void FinshedTaskTab::UpdateData(){
    g_index = 0;
    CGFTTraverse(VisitPrintf);
    tableView->setModel(student_model);
}

//! [0]
FinshedTaskTab::FinshedTaskTab(QWidget *parent)
{
    Q_UNUSED(parent);

   // descriptionLabel = new QLabel(tr("There are currently no contacts in your address book. "
       //                               "\nClick Add to add new contacts."));


    mainLayout = new QVBoxLayout;
   // mainLayout->addWidget(descriptionLabel);

    //准备数据模型
    student_model = new QStandardItemModel();
    student_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("序号")));
    student_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("重构操作")));
    student_model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("实际计算方式")));
    student_model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("耗时")));
    student_model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("CPID")));
    student_model->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("源大小（字节）")));
    student_model->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("结果大小（字节）")));



    tableView = new QTableView;
    tableView->setModel(student_model);
    tableView->setSortingEnabled(true);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->verticalHeader()->hide();
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    //固定表格大小
    tableView->horizontalHeader()->setResizeMode(0, QHeaderView::Fixed);
    tableView->horizontalHeader()->setResizeMode(1, QHeaderView::Fixed);
    tableView->horizontalHeader()->setResizeMode(2, QHeaderView::Fixed);
    tableView->horizontalHeader()->setResizeMode(3, QHeaderView::Fixed);
    tableView->horizontalHeader()->setResizeMode(4, QHeaderView::Fixed);
    tableView->horizontalHeader()->setResizeMode(5, QHeaderView::Fixed);

    //设置表格的各列的宽度值
    tableView->setColumnWidth(0,70);
    tableView->setColumnWidth(1,70);
    tableView->setColumnWidth(2,100);
    tableView->setColumnWidth(3,100);
    tableView->setColumnWidth(4,70);
    tableView->setColumnWidth(5,150);
    mainLayout->addWidget(tableView);
    setLayout(mainLayout);

     /****************/
    g_taskTab=this;
   // PrintfFT();
    UpdateData();
}
//! [0]

FinshedTaskTab::~FinshedTaskTab(){
    //if(descriptionLabel!=NULL) delete descriptionLabel;
    if(mainLayout!=NULL) delete mainLayout;
    if(tableView!=NULL) delete tableView;
    if(student_model!=NULL)delete student_model;
}


