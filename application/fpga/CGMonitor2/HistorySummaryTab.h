#ifndef HISTORYSUMMARYTAB_H
#define HISTORYSUMMARYTAB_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QTableView;
class QStandardItemModel;
class QGroupBox;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
QT_END_NAMESPACE

//! [0]
class HistorySummaryTab : public QWidget
{
    Q_OBJECT

public:
    HistorySummaryTab(QWidget *parent=0);

    void UpdateData();

    void SetPaint(struct SummaryItem* pArmItem,struct SummaryItem* pFPGAItem);
    int m_index;

private:
    QLabel *descriptionLabel;
    QVBoxLayout *mainLayout;

   // QTableView *tableView;
    QStandardItemModel* student_model;
    //汇总信息的group边框
    QGroupBox* Totalgroup;
    QLabel* timeTotalArm;
    QLabel* timeTotalFPGA;
    QLabel* sizeTotalArm;
    QLabel* sizeTotalFPGA;
    QLabel* textTotalArm;
    QLabel* textTotalFPGA;
    QLabel* NumTotalArm;
    QLabel* NumTotalFPGA;
    QLabel* textTotalNum;
    QLabel* textARM;
    QLabel* textFPGA;
    QLabel* flagARM;
    QLabel* flagFPGA;
    QLabel* totalTimeNumber;
    QLabel* totalSizeNumber;
    QLabel* totalNumNumber;

    QPushButton* m_button1;
    QPushButton* m_button2;
    QPushButton* m_button3;


public slots:
    void slotButton1();
    void slotButton2();
    void slotButton3();

};
//! [0]
#endif // SUMMARYTAB_H
