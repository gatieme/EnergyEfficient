#ifndef CPUFREQUTILS_H
#define CPUFREQUTILS_H

#include <QObject>
#include <QDebug>



#include "cpufreqbase.h"


#ifdef __cplusplus
extern "C"
{
#endif

#include "cpufreq.h"

#include <sys/sysinfo.h>  // for get_nprocs(void) and get_nprocs_conf(void)

#ifdef __cplusplus
}
#endif




class CpuFreqUtils : public QObject
{
    Q_OBJECT
public:
    explicit CpuFreqUtils(QObject *parent = 0);



signals:

public slots:




protected :
    int                     m_cpuNumKernel;             //  系统中插入的CPU的数目(包括online和offline)
    int                     m_cpuNumAvaliable;          //  系统中可用的CPU数目(即onlie的CPU数目)
    QList<CpuFreqBase>      m_cpus;                     //  当前系统中CPU的集合



};
#endif // CPUFREQUTILS_H
