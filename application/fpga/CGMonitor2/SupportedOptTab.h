#ifndef SIPPORTEDOPTTAB_H
#define SIPPORTEDOPTTAB_H

#include <QWidget>
#include "fpgaCGMon.h"
#include <QQueue>
#include <QList>
QT_BEGIN_NAMESPACE
class QLabel;
class QGroupBox;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
QT_END_NAMESPACE

//! [0]


class SupportedOptTab : public QWidget
{
    Q_OBJECT

public:
    SupportedOptTab(QWidget *parent=0);
    ~SupportedOptTab();
    void showUpOpt(struct CGOptBaseInfo* pBasInfo);
    int m_index;//当前的序号
    struct CGOptBaseInfo* m_pCurSupported;//当前的“操作”
    QQueue<int> i;




private:

    QVBoxLayout *mainLayout;
    QVBoxLayout* hLayout;
    QPushButton* leftButton;
    QPushButton* rightButton;

    QGroupBox* operationDescriptionGroup;
    QLabel *cliOptSOPath;
    QLabel *srvOPtSOPath;
    QLabel *ipCorePath;
    QLabel *InitTime;
    QLabel* cliFuncName;
    QLabel* srvARMFuncName;
    QLabel* srvFPGAFuncName;
    QLabel *descriptionLabel;
    QLabel *timeLabel;

public slots:
    void SlotSupportButton1();
    void SlotSupportButton2();

};
//! [0]
#endif // SUMMARYTAB_H
