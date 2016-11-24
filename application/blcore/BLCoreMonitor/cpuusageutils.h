#ifndef CPUUSAGEUTILS_H
#define CPUUSAGEUTILS_H

#include <QObject>
#include <QDebug>

#ifdef __cplusplus
extern "C"
{
#endif

#include "cpuusage.h"

#ifdef __cplusplus
}
#endif



class CpuUsageUtils : public QObject
{
    Q_OBJECT
public:
    explicit CpuUsageUtils(QObject *parent = 0, unsigned int cpunums = 0);

    virtual ~CpuUsageUtils( )
    {

    }

    ///////////////////////////////////////////////////////////////////
    /// 1--CPU jiffies stat的操作接口
    ///////////////////////////////////////////////////////////////////

    /////////////////////
    ///  1.1--获取CPU的Jiffies Stat信息
    /////////////////////

    //  获取编号为cpuid的CPU的jiffies stat信息
    inline struct cpuusage_jiffies_stat *GetCpuJiffiesStat(unsigned int cpuid);

    //  获取系统中总的CPU jiffies stat信息
    inline struct cpuusage_jiffies_stat *GetTotalCpuJiffiesStat( );

    //  获取所有的cpu和总的jiffies stat信息
    inline cpuusage_jiffies_stat_list GetAllCpusJiffiesStat( );

    /////////////////////
    ///  1.2--更新CPU的Jiffies Stat信息
    /////////////////////

    //  更新编号为cpuid的CPU的jiffies stat信息
    struct cpuusage_jiffies_stat *UpdateCpuJiffiesStat(unsigned int cpuid);

    //  更新系统中总的CPU jiffies stat信息
    struct cpuusage_jiffies_stat *UpdateTotalCpuJiffiesStat( );

    //  更新所有的cpu和总的jiffies stat信息
    cpuusage_jiffies_stat_list  UpdateAllCpusJiffiesStat( );



    ///////////////////////////////////////////////////////////////////
    /// 2--CPU usage的操作接口
    ///////////////////////////////////////////////////////////////////

    /////////////////////
    ///  2.1--获取CPU的Jiffies Stat信息
    /////////////////////
    double GetCpuUsage(unsigned int cpuid);
    double GetTotalCpuUsage( );
    QList<double> GetAllCpusUsage( );

    /////////////////////
    ///  2.2--更新CPU的usage信息
    /////////////////////
    double UpdateCpuUsage(unsigned int cpuid);
    double UpdateTotalCpuUsage( );
    QList<double> UpdateAllCpusUsage( );
signals:

public slots:


protected:
    /// 对象创建时将数据更新到m_jiffiesStats和m_prevJiffiesStats
    ///
    /// 每次更新时
    /// *   清楚老旧的m_prevJiffiesStats数据
    /// *   将原来的jiffies Stats的数据保存到m_prevJiffiesStats
    /// *   将数据更新到m_jiffiesStats
    /// *   同时计算负载信息m_cpuusage即m_jiffiesStats和m_prevJiffiesStats的差值

    QList<double>                       m_cpuusgae;

    QList<cpuusage_jiffies_stat *>      m_jiffiesStats;

    unsigned    int                     m_cpunums;
private :
    QList<cpuusage_jiffies_stat *>      m_prevJiffiesStats;


    /// 初始化jiiffies stat信息到m_jiffiesStats
    unsigned int InitAllCpusJiffiesStat( );
    /// 清除旧的m_prevJiffiesStats信息
    unsigned int UninitPrevCpusJiffiesStat();
    ///  保存旧的m_jiffiesStats信息到m_prevJiffiesStats信息
    unsigned int CopyJiffiesStatsToPre( );
    /// 计算系统的cpu使用率
    QList<double>  CalcAllCpusUsage( );
    ///  输出jiffies stat的值
    void ShowCpuJiffiesStat(cpuusage_jiffies_stat *stat);
};

#endif // CPUUSAGEUTILS_H
