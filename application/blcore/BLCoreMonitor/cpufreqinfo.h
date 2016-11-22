#ifndef CPUFREQINFO_H
#define CPUFREQINFO_H

#include <QObject>
#include <QList>

#ifdef __cplusplus
extern "C"
{
#endif

#include "cpufreq.h"

#ifdef __cplusplus
}
#endif


// 每个CPU的结构体
class CpuFreqInfo : public QObject
{
    Q_OBJECT
public:
    explicit CpuFreqInfo(QObject *parent = 0);

    virtual ~CpuFreqInfo( )
    {
    }

    const unsigned int GetCpuId( ) const;

    const bool GetIsOnline( ) const;

    ///////////////////////////////////////////////////////////////////
    /// CPU信息CpuFreq的操作
    ///////////////////////////////////////////////////////////////////
    /////////////////////
    //  获取当前CPU的信息
    /////////////////////
    const CpuFreqInfo GetCpuInfo( );                    //  获取当前CPU完整信息
    const bool GetIsOnline( );                          //  当前CPU是否online
    const unsigned long GetTransitionLatency( );        //  当前cpu完成频率切换所需要的时间
    const unsigned long GetScalingMinFrequency( );      //  当前CPU的最小运行频率
    const unsigned long GetScalingMaxFrequency( );      //  当前CPU的最大运行频率
    const unsigned long GetScalingCurFrequency( );      //  当前CPU的当前运行频率
    const unsigned long GetCpuInfoMinFrequency( );      //  当前CPU的最小运行频率
    const unsigned long GetCpuInfoMaxFrequency( );      //  当前CPU的最大运行频率
    const unsigned long GetCpuInfoCurFrequency( );      //  当前CPU的当前运行频率
    const QList<struct cpufreq_available_frequencies> GetAvailableFrequencies( );   //  可用的CPU频率值
    const QList<struct cpufreq_available_governors> GetAvailableGovernors( );         //  可用的CPU频率调节器
    const struct cpufreq_policy*   GetCpuFreqPolicy( );

    /////////////////////
    //  更新当前CPU的信息
    /////////////////////
    const CpuFreqInfo UpdateCpuInfo( );                 //  获取当前CPU完整信息
    bool UpdateIsOnline( );                             //  当前CPU是否online
    const unsigned long UpdateTransitionLatency( );     //  当前cpu完成频率切换所需要的时间
    unsigned long UpdateScalingMinFrequency( );         //  当前CPU的最小运行频率
    unsigned long UpdateScalingMaxFrequency( );         //  当前CPU的最大运行频率
    unsigned long UpdateScalingCurFrequency( );         //  当前CPU的当前运行频率
    unsigned long UpdateCpuInfoMinFrequency( );         //  当前CPU的最小运行频率
    unsigned long UpdateCpuInfoMaxFrequency( );         //  当前CPU的最大运行频率
    unsigned long UpdateCpuInfoCurFrequency( );         //  当前CPU的当前运行频率
    QList<struct cpufreq_available_frequencies> UpdateAvailableFrequencies( );   //  可用的CPU频率值
    QList<struct cpufreq_available_governors> UpdateAvailableGovernors( );         //  可用的CPU频率调节器
    struct cpufreq_policy*   UpdateCpuFreqPolicy( );

signals:


public slots:


protected :
    unsigned int    m_cpuid;                      //  当前CPU的编号
    bool            m_isonline;                   //  当前CPU是否在线
    unsigned long   m_transitionLatency;          //  频率切换所消耗的时间


    struct cpufreq_policy                         *m_curPolicy;                  //  当前使用的cpufreq
    //  注意cpufreq_policy中包含了min, max和governor
    unsigned long   m_scalingMinFrequency;        //  理论上最小运行频率
    unsigned long   m_scalingMaxFrequency;        //  理论上最大运行频率
    unsigned long   m_scalingCurFrequency;        //  理论上当前运行频率

    unsigned long   m_cpuinfoMinFrequency;        //  硬件读取的实际最小运行频率
    unsigned long   m_cpuinfoMaxFrequency;        //  硬件读取的实际最大运行频率
    unsigned long   m_cpuinfoCurFrequency;        //  硬件读取的实际当前运行频率



    QList<struct cpufreq_available_frequencies>   m_availableFrequencies;       //  可用的CPU频率值
    QList<struct cpufreq_available_governors>     m_availableGovernors;         //  可用的CPU频率调节器

};

#endif // CPUFREQINFO_H
