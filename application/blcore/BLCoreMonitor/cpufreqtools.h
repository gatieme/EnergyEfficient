#ifndef __CPUFREQTOOL_H_INCLUDE__
#define __CPUFREQTOOL_H_INCLUDE__

#include <QObject>
#include <QDebug>



#include "cpufrequtils.h"
#include "cpuusageutils.h"

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
class CpuFreqTools : public QObject
{
    Q_OBJECT
public :
    static CpuFreqTools*  GetInstance( )           // 获取对象单例的指针
    {
        return const_cast<CpuFreqTools *>(CpuFreqTools::m_singleton);
    }

    virtual ~CpuFreqTools( );


    //  判断编号为cpuid的CPU是否被安装(exist|present)
    static bool IsCpuPresent(unsigned int cpuid);
    //  判断编号为cpuid的CPU是否活跃(online)
    static bool IsCpuOnline(unsigned int copuid);
    ///////////////////////////////////////////////////////////////////
    /// 1--CPU数目的操作
    ///////////////////////////////////////////////////////////////////

    /////////////////////
    //  1.1--获取CPU的数目
    /////////////////////
    inline unsigned long GetCpuNumKernel( );
    inline unsigned long GetCpuNumAvaliable( );
    inline struct cpufreq_affected_cpus* GetAffectedCpus(unsigned int cpuid);
    inline struct cpufreq_affected_cpus* GetRelatedCpus(unsigned int cpuid);
    inline struct cpufreq_stats* GetStats(unsigned int cpuid, unsigned long long *total_time);
    inline unsigned long GetTransitions(unsigned int cpuid);

    /////////////////////
    //  1.2--更新CPU的数目
    /////////////////////
    inline unsigned long UpdateCpuNumKernel( );
    inline unsigned long UpdateCpuNumAvaliable( );
    inline struct cpufreq_affected_cpus *UpdateAffectedCpus(unsigned int cpuid);
    inline struct cpufreq_affected_cpus* UpdateRelatedCpus(unsigned int cpuid);
    inline struct cpufreq_stats* UpdateStats(unsigned int cpuid, unsigned long long *total_time);
    inline unsigned long UpdateTransitions(unsigned int cpuid);

    /////////////////////
    //  1.3--设置CPU的数目
    /////////////////////
    //unsigned long SetCpuNumKernel( );
    //unsigned long SetCpuNumAvaliable( );

    ///////////////////////////////////////////////////////////////////
    /// 2--CPU信息CpuFreq的操作
    ///////////////////////////////////////////////////////////////////
    /////////////////////
    //  2.1--获取编号为cpuid的CPU的信息
    /////////////////////
    inline CpuFreqUtils* GetCpuInfo(unsigned int cpuid);      //  获取编号为cpuid的CPU完整信息
    inline const bool GetIsOnline(unsigned int cpuid);                  //  编号为cpuid的CPU是否online
    inline const unsigned long GetScalingMinFrequency(unsigned int cpuid);   //  编号为cpuid的CPU的最小运行频率
    inline const unsigned long GetScalingMaxFrequency(unsigned int cpuid);   //  编号为cpuid的CPU的最大运行频率
    inline const unsigned long GetScalingCurFrequency(unsigned int cpuid);   //  编号为cpuid的CPU的当前运行频率
    inline const unsigned long GetCpuInfoMinFrequency(unsigned int cpuid);   //  编号为cpuid的CPU的最小运行频率
    inline const unsigned long GetCpuInfoMaxFrequency(unsigned int cpuid);   //  编号为cpuid的CPU的最大运行频率
    inline const unsigned long GetCpuInfoCurFrequency(unsigned int cpuid);   //  编号为cpuid的CPU的当前运行频率
#if defined(CNODE_IN_QLIST)
    //一种是将节点重新组织在QList中
    inline QList<struct cpufreq_available_frequencies *>& GetAvailableFrequencies(unsigned int cpuid);   //  可用的CPU频率值
    inline QList<struct cpufreq_available_governors *>& GetAvailableGovernors(unsigned int cpuid);         //  可用的CPU频率调节器
#elif defined(CLIST_TO_QLIST)
    //另一种是近将节点的数据域组织在QList, 即将CLIST转换为QLIST
    inline QList<QString>& GetAvailableFrequencies(unsigned int cpuid);   //  可用的CPU频率值
    inline QList<unsigned long>& GetAvailableGovernors(unsigned int cpuid);         //  可用的CPU频率调节器
#elif defined(USE_CLIST)
    //另外一种方式是直接使用CLIST
    inline struct cpufreq_available_frequencies *GetAvailableFrequencies(unsigned int cpuid);   //  可用的CPU频率值
    inline struct cpufreq_available_governors *GetAvailableGovernors(unsigned int cpuid);         //  可用的CPU频率调节器
#endif
    inline const struct cpufreq_policy*   GetCpuFreqPolicy(unsigned int cpuid);

    /////////////////////
    //  2.2--更新编号为cpuid的CPU的信息
    /////////////////////
    inline CpuFreqUtils* UpdateCpuInfo(unsigned int cpuid);      //  获取编号为cpuid的CPU完整信息
    inline bool UpdateIsOnline(unsigned int cpuid);                  //  编号为cpuid的CPU是否online
    inline unsigned long UpdateScalingMinFrequency(unsigned int cpuid);   //  编号为cpuid的CPU的最小运行频率
    inline unsigned long UpdateScalingMaxFrequency(unsigned int cpuid);   //  编号为cpuid的CPU的最大运行频率
    inline unsigned long UpdateScalingCurFrequency(unsigned int cpuid);   //  编号为cpuid的CPU的当前运行频率
    inline unsigned long UpdateInfoMinFrequency(unsigned int cpuid);   //  编号为cpuid的CPU的最小运行频率
    inline unsigned long UpdateCpuInfoMaxFrequency(unsigned int cpuid);   //  编号为cpuid的CPU的最大运行频率
    inline unsigned long UpdateCpuInfoCurFrequency(unsigned int cpuid);   //  编号为cpuid的CPU的当前运行频率
#if defined(CNODE_IN_QLIST)
    //一种是将节点重新组织在QList中
    inline QList<struct cpufreq_available_frequencies *>& UpdateAvailableFrequencies(unsigned int cpuid);   //  可用的CPU频率值
    inline QList<struct cpufreq_available_governors *>& UpdateAvailableGovernors(unsigned int cpuid);         //  可用的CPU频率调节器
#elif defined(CLIST_TO_QLIST)
    //另一种是近将节点的数据域组织在QList, 即将CLIST转换为QLIST
    inline QList<QString>& UpdateAvailableFrequencies(unsigned int cpuid);   //  可用的CPU频率值
    inline QList<unsigned long >& UpdateAvailableGovernors(unsigned int cpuid);         //  可用的CPU频率调节器
#elif defined(USE_CLIST)
    //另外一种方式是直接使用CLIST
    inline struct cpufreq_available_frequencies *UpdateAvailableFrequencies(unsigned int cpuid);   //  可用的CPU频率值
    inline struct cpufreq_available_governors *UpdateAvailableGovernors(unsigned int cpuid);         //  可用的CPU频率调节器
#endif
    inline struct cpufreq_policy*   UpdateCpuFreqPolicy(unsigned int cpuid);


    /////////////////////
    //  2.3--设置编号为cpuid的CPU的信息
    /////////////////////
    bool SetPolicy(unsigned int cpuid, struct cpufreq_policy *policy);
    bool SetPolicyMin(unsigned int cpuid, unsigned long min_freq);
    bool SetPolicyMax(unsigned int cpuid, unsigned long max_freq);
    bool SetPolicyGovernor(unsigned int cpuid, QString *governor);
    bool SetFrequency(unsigned int cpuid, unsigned long targetFrequency);


    ///////////////////////////////////////////////////////////////////
    /// 3--CPU信息CpuUsage的操作
    ///////////////////////////////////////////////////////////////////
    double UpdateCpuUsage(unsigned int cpuid);          //  获取编号为cpuid的CPU的usage信息
    double UpdateTotalUsage( );                         //  获取系统中总的cpuusage信息

private:
    explicit CpuFreqTools(QObject *parent = 0);

    explicit CpuFreqTools(const CpuFreqTools &singleton)       // 赋值构造函数[被保护]
    {
    }



signals:

public slots:
    ///////////////////////////////////////////////////////////////////
    /// 3--CPU
    ///////////////////////////////////////////////////////////////////
    /////////////////////
    //  3.1--获取编号为cpuid的CPU-freq的信息
    /////////////////////
    QList<unsigned long> UpdateAllCpusScalingCurFrequency(unsigned int cpuid);   //  CPU的当前运行频率
    QList<unsigned long> UpdateAllCpusCpuInfoCurFrequency(unsigned int cpuid);   //  当前运行频率
    /////////////////////
    //  3.2--获取编号为cpuid的CPU-usage的信息
    /////////////////////
    QList<double> UpdateAllCpusUsage(unsigned int cpuid);                 //  当前运行频率

protected :
    ///  m_cpuNumKernel     the number of processors configured by the operating system.
    ///  m_cpuNumAvaliable  the number of processors currently available in the system.
    ///  This may be less than the number returned by get_nprocs_conf( )
    ///   because processors may be offline (e.g., on hotpluggable systems).
    int                      m_cpuNumKernel;             //  系统中插入的CPU的数目(包括online和offline)
    int                      m_cpuNumAvailable;          //  系统中可用的CPU数目(即onlie的CPU数目)
    QList<CpuFreqUtils *>    m_cpufreqs;                 //  当前系统中CPU频率操作的集合
    QList<CpuUsageUtils *>   m_cpuusages;                //  当前系统中CPU使用率的集合
    //  单例模式
    static CpuFreqTools     *m_singleton;

    class GC
    {
      public :
        ~GC( )
        {
            if (CpuFreqTools::m_singleton != NULL)
            {
                delete m_singleton;
                m_singleton = NULL ;
            }
        }
        static GC gc;
    };
};




#endif // __CPUFREQTOOL_H_INCLUDE__
