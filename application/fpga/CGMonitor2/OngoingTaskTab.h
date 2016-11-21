#ifndef ONGOINGTASKTAB_H
#define ONGOINGTASKTAB_H

#include <QWidget>
#include <QtGui>
QT_BEGIN_NAMESPACE
class QLabel;
class QVBoxLayout;

QT_END_NAMESPACE

#include "ccmessage.h"



class TreeView :public QTreeView
{
public:
    TreeView();
    void iterateOverItems();
    QList<QStandardItem*> returnTheItems();
    void mouseDoubleClickEvent(QMouseEvent *event);

    QStandardItemModel *student_model;
    private:
};




//! [0]
class OngoingTaskTab : public QWidget
{
    Q_OBJECT

public:
    OngoingTaskTab(QWidget *parent=0);
    ~OngoingTaskTab();
    void InserOngingtToList(struct OngoningTask* pTask,int index);

   //  为了显示大任务分割
    QList<QStandardItem *> g_listcolums; //最多5个大任务
    int g_rowIndex;//大任务外壳程序的显示行
    int g_ParentIndex;
    QStandardItem* g_QStandardItem;
    void UpdateData();


private:
    QLabel *descriptionLabel;
    QVBoxLayout *mainLayout;
    QGroupBox* FPGA_Migrate;
    //QTableView * tableView;
     QLineEdit* indexedit;
    QStandardItemModel* student_model;
    TreeView* treeView;
 public slots:
    void slotsMigrate();
    void slotsMigrateFPGA();
};
//! [0]
#endif // SUMMARYTAB_H
