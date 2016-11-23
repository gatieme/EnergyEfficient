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
    //  1.1--获取CPU的usage信息
    /////////////////////
    double GetCpuJiffiesStat(unsigned int cpuid);
    double GetTotalCpuJiffiesStat( );

    /////////////////////
    //  1.2--更新CPU的usage信息
    /////////////////////
    double UpdateCpuJiffiesStat(unsigned int cpuid);
    double UpdateTotalCpuJiffiesStat( );
signals:

public slots:


protected:
    QList<cpuusage_jiffies_stat>    m_jiffiesStats;
};

#endif // CPUUSAGEUTILS_H
