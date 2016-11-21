#ifndef SUMMARYTAB_H
#define SUMMARYTAB_H

#include <QWidget>
QT_BEGIN_NAMESPACE
class QLabel;
class QProgressBar;
class QGroupBox;
class QVBoxLayout;
class QHBoxLayout;
class QRadioButton;
class QSpacerItem;
class QPushButton;
class QGridLayout;
class QCheckBox;
QT_END_NAMESPACE


#include "IniEx.h"
#include "ccmessage.h"

typedef struct PACKED{
    char name[20];
    unsigned int user;
    unsigned int nice;
    unsigned int system;
    unsigned int idle;


}CPU_OCCUPY;


class UtilizationDialog : public QWidget{
 Q_OBJECT
public:
    UtilizationDialog(QWidget *parent=0,QString opt="DES");
    void Init();
    void SetData();
    int a[10];
    ~UtilizationDialog();

    QProgressBar* register_progress;
    QProgressBar* LUTs_progress;
    QProgressBar* Logic_progress;
    QProgressBar* Memory_progress;
    QProgressBar* Slices_progress;
    QProgressBar* LUT_FF_pairs_progress;
    QProgressBar* Bonded_IOBs_progress;
    QProgressBar* BlockRam_FIFO_progress;
    QProgressBar* Total_Memory_progress;
    QProgressBar* BUFG_BUFGCTRLs_progress;

    QLabel* Label1;
    QLabel* Label2;
    QLabel* Label3;
    QLabel* Label4;
    QLabel* Label5;
    QLabel* Label6;
    QLabel* Label7;
    QLabel* Label8;
    QLabel* Label9;
    QLabel* Label10;

    QLabel* Label11;
    QLabel* Label21;
    QLabel* Label31;
    QLabel* Label41;
    QLabel* Label51;
    QLabel* Label61;
    QLabel* Label71;
    QLabel* Label81;
    QLabel* Label91;
    QLabel* Label101;


    QPushButton* exitButton;
    QGridLayout *layout;


public slots:
   // void slotsExit();


};


//! [0]
class SummaryTab : public QWidget
{
    Q_OBJECT

public:
    SummaryTab(QWidget *parent=0);
    void UpdateData();
    int m_fd;
    int m_oldIOSubType;
    QString OptName;
    QString m_IPPATH;
    CPU_OCCUPY old;
    int M_model;
    int m_model_flag;
void ShowIPConfigMessage(QString IPPATH);
public slots:
    void setCpuPersent(int persent); //0---100的值，其它值非法
    void setFPGAUsePercent(int persent);//0---100的值，其它值非法
    void setIPCorePath(QString Path); //Path路径
    void setSubcardType(QString typeName); //子板的名称
    void setRunningType(int typeRunning);    //0---运行中  1---配置中  2---空闲中
    void setCGModelSlots(const int model);  //重构的模式  1---禁止FPGA重构  2--强制FPGA重构，其它--正常模式

    void SlotsetFPGANormal(bool checked);
    void SlotsetFPGAForbidden(bool checked);
    void SlotsetFPGAForce(bool checked);

    void slotFPGAUtilization();
    void SlotsetFPGAUseFirst(bool checked);

    void slotCheckBoxRS232(bool);
    void slotCheckBoxRS422(bool);
    void slotCheckBoxRS485(bool);
    void slotCheckBoxCAN(bool);
signals:
    void setCGModelSignals(const int model);  //重构的模式  1---禁止FPGA重构  2--强制FPGA重构，其它--正常模式


private:  //界面显示相关
    //使用率  组的所有标签
    QLabel* FPGA_used;
    QLabel* CPU_used;
    QLabel* FPGA_used_percent;
    QLabel* CPU_used_percent;
    QProgressBar* fpga_used_progress;
    QProgressBar* cpu_used_progress;
    QGroupBox* used_group_box;


    //FPGA 详细信息组
    QLabel* IPCorePath;
    QLabel* SubTypeName;
    QLabel* HandleModel;
    QLabel* Running;
    QGroupBox* FPGA_scription;
    QPushButton* UtilizationButton;

    //FPGA 详细信息组
    QGroupBox* FPGA_Config;

    QGroupBox* FPGA_Config_Strtegy;//设置FPGA状态的按钮
    QRadioButton* setFPGANormal;
    QRadioButton* setFPGAForbidden;
    QRadioButton* setFPGAMust;
    QRadioButton* setUseFirst;


    QGroupBox* FPGA_support_IOType;//设置支持的IO接口
    QCheckBox* subType_RS232;
    QCheckBox* subType_RS485;
    QCheckBox* subType_RS422;
    QCheckBox* subType_CAN;




    QLabel *descriptionLabel;
    QVBoxLayout *mainLayout;


};
//! [0]
#endif // SUMMARYTAB_H
