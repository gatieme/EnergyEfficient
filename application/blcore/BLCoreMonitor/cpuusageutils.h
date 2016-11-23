#ifndef CPUUSAGEUTILS_H
#define CPUUSAGEUTILS_H

#include <QObject>
#include "cpuusage.h"

class CpuUsageUtils : public QObject
{
    Q_OBJECT
public:
    explicit CpuUsageUtils(QObject *parent = 0);

    virtual ~CpuUsageUtils( )
    {

    }

    ///////////////////////////////////////////////////////////////////
    /// 1--CPU使用率usage的操作接口
    ///////////////////////////////////////////////////////////////////

    /////////////////////
    ///  1.1--获取CPU的Jiffies Stat信息
    /////////////////////
    struct cpuusage_jiffies_stat *GetCpuJiffiesStat(unsigned int cpuid);
    struct puusage_jiffies_stat *GetTotalCpuJiffiesStat( );


    /////////////////////
    ///  1.2--更新CPU的Jiffies Stat信息
    /////////////////////
    struct cpuusage_jiffies_stat *UpdateCpuJiffiesStat(unsigned int cpuid);
    struct cpuusage_jiffies_stat *UpdateTotalCpuJiffiesStat( );


    /////////////////////
    ///  1.2--更新CPU的usage信息
    /////////////////////
    /// 使用如下函数可能会导致延迟
    /// 因为计算cpuusage需要练习一段时间间隔获取cpu jiffies stat的信息
    double UpdateCpuUsage(unsigned int cpuid, unsigned int delay);
    double UpdateTotalCpuUsage(unsigned int delay);
signals:

public slots:


protected:
    QList<cpuusage_jiffies_stat>    m_jiffiesStats;
};

#endif // CPUUSAGEUTILS_H
