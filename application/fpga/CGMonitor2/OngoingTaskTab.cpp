

#include "OngoingTaskTab.h"
#include "fpgaCGMon.h"
#include "fpga/fpgaCG.h"

TreeView::TreeView() : QTreeView()
 {
 //QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
//准备数据模型
    student_model = new QStandardItemModel(1,7);
    student_model->setHeaderData(0, Qt::Horizontal, tr("序号"));
    student_model->setHeaderData(1, Qt::Horizontal, tr("重构操作"));
    student_model->setHeaderData(2, Qt::Horizontal, tr("用户计算方式"));
    student_model->setHeaderData(3, Qt::Horizontal, tr("实际计算方式"));
    student_model->setHeaderData(4, Qt::Horizontal, tr("时间戳"));
    student_model->setHeaderData(5, Qt::Horizontal, tr("CPID"));
    student_model->setHeaderData(6, Qt::Horizontal, tr("源大小（字节）"));

 this->setModel(student_model);


 //设置表格的各列的宽度值
 this->setColumnWidth(0,70);
 this->setColumnWidth(1,100);
 this->setColumnWidth(2,100);
 this->setColumnWidth(3,100);
 this->setColumnWidth(4,100);
    this->expandAll();




}


QList<QStandardItem*> TreeView::returnTheItems() {
 return student_model->findItems("*", Qt::MatchWildcard | Qt::MatchRecursive);
}
void TreeView::iterateOverItems()
{
 QList<QStandardItem*> list = returnTheItems();

 foreach (QStandardItem* item, list) {
    qDebug() << item->text();
 }
}
 void TreeView::mouseDoubleClickEvent(QMouseEvent *event)
{
 if (event->button() == Qt::LeftButton) {
 QModelIndex index0 = currentIndex();
 qDebug() << index0.data().toString();
 }
}



static OngoingTaskTab* g_taskTab;
static int g_index;
static void VisitPrintf(struct OngoningTask* task){


    if(task ==NULL) return;

     g_taskTab->InserOngingtToList(task,g_index++);

}


void OngoingTaskTab::InserOngingtToList(struct OngoningTask* pTask,int row){
    if(pTask==NULL || row<0) return;
    static int countIndx=0;
    if(pTask->index == pTask->parent_index){
        treeView->student_model->setItem(row,0,new QStandardItem(tr("%1").arg(pTask->index)));
        treeView->student_model->setItem(row,1,new QStandardItem(CGOPFOFindOptNameByIndex(pTask->optType)));
        treeView->student_model->setItem(row,2,new QStandardItem((pTask->ArmOrFPGA==1)?"ARM":(pTask->ArmOrFPGA==2)?"FPGA":"Any"));
        treeView->student_model->setItem(row,3,new QStandardItem((pTask->realHow==1)?"ARM":(pTask->realHow==2)?"FPGA":(pTask->realHow==4)?"ARM+FPGA":"InQueue"));

        treeView->student_model->setItem(row,4,new QStandardItem(tr("%1").arg(pTask->StartTime)));
        treeView->student_model->setItem(row,5,new QStandardItem(tr("%1").arg(pTask->Cli_pid)));
        treeView->student_model->setItem(row,6,new QStandardItem(tr("%1").arg(pTask->sourMemSize)));
        //this->student_model->setItem(row,6,new QStandardItem(tr("%1").arg(pTask->tarMemSize)));

    }else if(pTask->parent_index==-1){ //外壳程序
        g_rowIndex=row;
        g_ParentIndex=pTask->index;
        g_QStandardItem=new QStandardItem(tr("%1").arg(pTask->index));
        treeView->student_model->setItem(row,0,g_QStandardItem);
        treeView->student_model->setItem(row,1,new QStandardItem(CGOPFOFindOptNameByIndex(pTask->optType)));

        treeView->student_model->setItem(row,2,new QStandardItem((pTask->ArmOrFPGA==1)?"ARM":(pTask->ArmOrFPGA==2)?"FPGA":"Any"));
        treeView->student_model->setItem(row,3,new QStandardItem((pTask->realHow==1)?"ARM":((pTask->realHow==2)?"FPGA":((pTask->realHow==3)?"ARM+FPGA":"InQueue"))));
        treeView->student_model->setItem(row,4,new QStandardItem(tr("%1").arg(pTask->StartTime)));
        treeView->student_model->setItem(row,5,new QStandardItem(tr("%1").arg(pTask->Cli_pid)));
        treeView->student_model->setItem(row,6,new QStandardItem(tr("%1").arg(pTask->sourMemSize)));
    countIndx=0;

    }else{ //
       // QList<QStandardItem *> g_listcolums[5]; //最多5个大任务
        //int g_rowIndex[5];//大任务外壳程序的显示行
        //1.查找Parent

        if(g_rowIndex<0 || g_QStandardItem==NULL) return;

        QStandardItem* rootLabel = g_QStandardItem;
        //2.插入到Parent
        //parent = treeView->student_model->index(0, 0, parent);
        //treeView->student_model->insertRow(row,parent);

        //QModelIndex index = treeView->student_model->index(0, 0, parent);
        //treeView->student_model->setData(index, row);
        QList<QStandardItem *>* g_listcolums = new  QList<QStandardItem *>();
        QStandardItem* parent= new QStandardItem();
        QStandardItem* head;
        parent->setColumnCount(7);
        head = new QStandardItem(tr("%1").arg(pTask->index));

        rootLabel->appendRow(head);
        rootLabel->setChild(countIndx,1,new QStandardItem(CGOPFOFindOptNameByIndex(pTask->optType)));
        rootLabel->setChild(countIndx,2,new QStandardItem((pTask->ArmOrFPGA==1)?"ARM":(pTask->ArmOrFPGA==2)?"FPGA":"Any"));
        rootLabel->setChild(countIndx,3,new QStandardItem((pTask->realHow==1)?"ARM":(pTask->realHow==2)?"FPGA":(pTask->realHow==4)?"ARM+FPGA":"InQueue"));
        rootLabel->setChild(countIndx,4,new QStandardItem(tr("%1").arg(pTask->StartTime)));
        rootLabel->setChild(countIndx,5,new QStandardItem(tr("%1").arg(pTask->Cli_pid)));
        rootLabel->setChild(countIndx,6,new QStandardItem(tr("%1").arg(pTask->sourMemSize)));
        countIndx++;

    }



    // QStandardItem *item5 = new QStandardItem("fifth");
    // item4->appendRow(item5);
    // QModelIndex parent;
    // for (int i = 0; i < 4; ++i) {
    //     parent = model->index(0, 0, parent);
    //     model->insertRows(0, 1, parent);
    //     model->insertColumns(0, 1, parent);
    //     QModelIndex index = model->index(0, 0, parent);
    //     model->setData(index, i);
    // }

}


void OngoingTaskTab::UpdateData(){
    g_index = 0;
    treeView->student_model->removeRow(0);
    g_rowIndex=-1;//大任务外壳程序的显示行
    g_ParentIndex =-1;
   /* delete g_QStandardItem;
    g_QStandardItem=NULL;
*/
    CGOGTTraverse(VisitPrintf);
    treeView->expandAll();
    /*if(g_index==0){ //清空任务分割显示
        if(g_QStandardItem!=NULL){
            g_QStandardItem->removeRows(0,g_QStandardItem->rowCount());
        }
    }*/
    int row;
    row =0;
    int timestamp = 467824+rand()%100;
   /* QStandardItem* rootLabel;
    if(1){
        rootLabel = new QStandardItem(tr("%1").arg(2));
        treeView->student_model->setItem(row,0,rootLabel);
        treeView->student_model->setItem(row,1,new QStandardItem(tr("DES")));
        treeView->student_model->setItem(row,2,new QStandardItem("ARM+FPGA"));


        treeView->student_model->setItem(row,3,new QStandardItem(tr("%1").arg(timestamp)));
        treeView->student_model->setItem(row,4,new QStandardItem(tr("%1").arg(32452)));
        treeView->student_model->setItem(row,5,new QStandardItem(tr("%1").arg(1024*1024)));

    }


    QModelIndex parent;
   for(row=1;row<9;row++){
        //parent = treeView->student_model->index(0, 0, parent);
        //treeView->student_model->insertRow(row,parent);

        //QModelIndex index = treeView->student_model->index(0, 0, parent);
        //treeView->student_model->setData(index, row);

        QList<QStandardItem *> listcolums;
        listcolums.append(new QStandardItem(tr("%1").arg(2+row)));
        listcolums.append(new QStandardItem(tr("DES")));
         int arm = rand()%2;timestamp +=rand()%100;
        listcolums.append(new QStandardItem((arm==1)?"ARM":"FPGA"));
        listcolums.append(new QStandardItem(tr("%1").arg(timestamp)));
        listcolums.append(new QStandardItem(tr("%1").arg(32452)));
        listcolums.append(new QStandardItem(tr("%1").arg(1024*128)));


        //QStandardItem* colums = new QStandardItem(listcolums);
        //colums->appendRow(listcolums);
        rootLabel->appendRow(listcolums);

    }*/

}


void OngoingTaskTab::slotsMigrate(){

    g_CCMessage->showText(tr("开始任务迁移到ARM...."),5);
    //usleep(1000*1000*5);
    int index =indexedit->text().toInt();
    if(index>0){
        CGCliMigrateTask(index,1);
        g_CCMessage->changeText(tr("任务迁移到ARM....\n....\n成功!!"));
    }


}

void OngoingTaskTab::slotsMigrateFPGA(){

    g_CCMessage->showText(tr("开始任务迁移到FPGA...."),5);
    //usleep(1000*1000*5);
    int index =indexedit->text().toInt();
    if(index>0){
        CGCliMigrateTask(index,2);
        g_CCMessage->changeText(tr("任务迁移到FPGA....\n....\n成功!!"));
    }


}



//! [0]
OngoingTaskTab::OngoingTaskTab(QWidget *parent)
{
     Q_UNUSED(parent);


    QHBoxLayout* layout1 = new QHBoxLayout;
    QPushButton* button1 = new QPushButton(tr("迁移到ARM"));
    QPushButton* button2 = new QPushButton(tr("迁移到FPGA"));
    indexedit = new QLineEdit();
    QLabel* label = new QLabel(tr("任务序号"));
    layout1->addWidget(label);
    layout1->addWidget(indexedit);
    layout1->addWidget(button1);
    layout1->addWidget(button2);

    connect(button1,SIGNAL(clicked()),this,SLOT(slotsMigrate()));
    connect(button2,SIGNAL(clicked()),this,SLOT(slotsMigrateFPGA()));

    treeView = new TreeView();

     FPGA_Migrate=  new QGroupBox(tr("任务迁移"));
     FPGA_Migrate->setLayout(layout1);
     //布局
     mainLayout = new QVBoxLayout;
     mainLayout->addWidget(treeView);
     mainLayout->addWidget(FPGA_Migrate);
     setLayout(mainLayout);

     /****************/

    //g_listcolums= new QStandardItem(tr("%1").arg(2));
    g_rowIndex=-1;//大任务外壳程序的显示行
    g_ParentIndex =-1;
    g_QStandardItem = NULL;
     g_taskTab = this;

     //UpdateData();

     //PrintfOGT();
     QShortcut *Key_1 = new QShortcut(QKeySequence(Qt::Key_A),this);
     connect(Key_1,SIGNAL(activated()),this,SLOT(slotsMigrate()));

     QShortcut *Key_5 = new QShortcut(QKeySequence(Qt::Key_F),this);
     connect(Key_5,SIGNAL(activated()),this,SLOT(slotsMigrateFPGA()));

     QShortcut *Key_2 = new QShortcut(QKeySequence(Qt::Key_Space),this);
     connect(Key_2,SIGNAL(activated()),indexedit,SLOT(setFocus()));
}
//! [0]

OngoingTaskTab::~OngoingTaskTab(){

    //if(descriptionLabel!=NULL) delete descriptionLabel;
    if(mainLayout!=NULL) delete mainLayout;
    //if(tableView!=NULL) delete tableView;
    if(student_model!=NULL)delete student_model;
}
