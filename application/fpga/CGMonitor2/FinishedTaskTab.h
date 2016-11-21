#ifndef FINSHEDTASKTAB_H
#define FINSHEDTASKTAB_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QVBoxLayout;
class QTableView;
class QStandardItemModel;
QT_END_NAMESPACE

//! [0]
class FinshedTaskTab : public QWidget
{
    Q_OBJECT

public:
    FinshedTaskTab(QWidget *parent=0);
    ~FinshedTaskTab();
    void InserOngingtToList(struct FinishedTask* pTask,int index);


    void UpdateData();

private:
    QLabel *descriptionLabel;
    QVBoxLayout *mainLayout;
    QTableView *tableView;
    QStandardItemModel* student_model;
};
//! [0]
#endif // SUMMARYTAB_H
