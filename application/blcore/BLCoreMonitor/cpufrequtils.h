#ifndef CPUFREQUTILS_H
#define CPUFREQUTILS_H

#include <QObject>
#include <QDebug>



#include "cpufreqinfo.h"


#ifdef __cplusplus
extern "C"
{
#endif

#include "cpufreq.h"

#include <sys/sysinfo.h>  // for get_nprocs(void) and get_nprocs_conf(void)

#ifdef __cplusplus
}
#endif



//  该工具可以设计为单例
//  也可以在主窗体中初始化, 并被所有窗体共享
class CpuFreqUtils : public QObject
{
    Q_OBJECT
public :
    static CpuFreqUtils*  GetInstance( )           // 获取对象单例的指针
    {
        return const_cast<CpuFreqUtils *>(CpuFreqUtils::m_singleton);
    }
    ///////////////////////////////////////////////////////////////////
    /// CPU数目的操作
    ///////////////////////////////////////////////////////////////////

    /////////////////////
    //  获取CPU的数目
    /////////////////////
    unsigned long GetCpuNumKernel( );
    unsigned long GetCpuNumAvaliable( );
    /////////////////////
    //  更新CPU的数目
    /////////////////////
    unsigned long UpdateCpuNumKernel( );
    unsigned long UpdateCpuNumAvaliable( );
    /////////////////////
    //  设置CPU的数目
    /////////////////////
    //unsigned long SetCpuNumKernel( );
    //unsigned long SetCpuNumAvaliable( );

    ///////////////////////////////////////////////////////////////////
    /// CPU信息CpuFreq的操作
    ///////////////////////////////////////////////////////////////////
    /////////////////////
    //  获取编号为cpuid的CPU的信息
    /////////////////////
    const CpuFreqInfo GetCpuInfo(unsigned int cpuid);      //  获取编号为cpuid的CPU完整信息
    const bool GetIsOnline(unsigned int cpuid);                  //  编号为cpuid的CPU是否online
    const unsigned long GetScalingMinFrequency(unsigned int cpuid);   //  编号为cpuid的CPU的最小运行频率
    const unsigned long GetScalingMaxFrequency(unsigned int cpuid);   //  编号为cpuid的CPU的最大运行频率
    const unsigned long GetScalingCurFrequency(unsigned int cpuid);   //  编号为cpuid的CPU的当前运行频率
    const unsigned long GetCpuInfoMinFrequency(unsigned int cpuid);   //  编号为cpuid的CPU的最小运行频率
    const unsigned long GetCpuInfoMaxFrequency(unsigned int cpuid);   //  编号为cpuid的CPU的最大运行频率
    const unsigned long GetCpuInfoCurFrequency(unsigned int cpuid);   //  编号为cpuid的CPU的当前运行频率
    const QList<struct cpufreq_available_frequencies> GetAvailableFrequencies(unsigned int cpuid);   //  可用的CPU频率值
    const QList<struct cpufreq_available_governors> GetAvailableGovernors(unsigned int cpuid);         //  可用的CPU频率调节器
    const struct cpufreq_policy   GetCpuFreqPolicy(unsigned int cpuid);

    /////////////////////
    //  更新编号为cpuid的CPU的信息
    /////////////////////
    const CpuFreqInfo UpdateCpuInfo(unsigned int cpuid);      //  获取编号为cpuid的CPU完整信息
    bool UpdateIsOnline(unsigned int cpuid);                  //  编号为cpuid的CPU是否online
    unsigned long UpdateScalingMinFrequency(unsigned int cpuid);   //  编号为cpuid的CPU的最小运行频率
    unsigned long UpdateScalingMaxFrequency(unsigned int cpuid);   //  编号为cpuid的CPU的最大运行频率
    unsigned long UpdateScalingCurFrequency(unsigned int cpuid);   //  编号为cpuid的CPU的当前运行频率
    unsigned long UpdateInfoMinFrequency(unsigned int cpuid);   //  编号为cpuid的CPU的最小运行频率
    unsigned long UpdateCpuInfoMaxFrequency(unsigned int cpuid);   //  编号为cpuid的CPU的最大运行频率
    unsigned long UpdateCpuInfoCurFrequency(unsigned int cpuid);   //  编号为cpuid的CPU的当前运行频率
    QList<struct cpufreq_available_frequencies> UpdateAvailableFrequencies(unsigned int cpuid);   //  可用的CPU频率值
    QList<struct cpufreq_available_governors> UpdateAvailableGovernors(unsigned int cpuid);         //  可用的CPU频率调节器
    struct cpufreq_policy   UpdateCpuFreqPolicy(unsigned int cpuid);



private:
    explicit CpuFreqUtils(QObject *parent = 0);

    CpuFreqUtils(const CpuFreqUtils &singleton)       // 赋值构造函数[被保护]
    {
    }


signals:

public slots:




protected :
    ///  m_cpuNumKernel     the number of processors configured by the operating system.
    ///  m_cpuNumAvaliable  the number of processors currently available in the system.
    ///  This may be less than the number returned by get_nprocs_conf( )
    ///   because processors may be offline (e.g., on hotpluggable systems).
    int                     m_cpuNumKernel;             //  系统中插入的CPU的数目(包括online和offline)
    int                     m_cpuNumAvaliable;          //  系统中可用的CPU数目(即onlie的CPU数目)
    QList<CpuFreqInfo>      m_cpus;                     //  当前系统中CPU的集合

    //  单例模式
    static CpuFreqUtils     *m_singleton;

    class GC
    {
      public :
        ~GC( )
        {
            if (CpuFreqUtils::m_singleton != NULL)
            {
                delete m_singleton;
                m_singleton = NULL ;
            }
        }
        static GC gc;
    };
};




#endif // CPUFREQUTILS_H
