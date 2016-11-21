#ifndef CPUFREQ_H
#define CPUFREQ_H

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
class CpuFreqBase : public QObject
{
    Q_OBJECT
public:
    explicit CpuFreqBase(QObject *parent = 0);

signals:

public slots:

protected :
    unsigned int    m_cpuid;                      //  当前CPU的编号
    bool   m_isonline;                   //  当前CPU是否在线

    unsigned long   m_scalingMinFrequency;        //  理论上最小运行频率
    unsigned long   m_scalingMaxFrequency;        //  理论上最大运行频率
    unsigned long   m_scalingCurFrequency;        //  理论上当前运行频率

    unsigned long   m_cpuinfoMinFrequency;        //  硬件读取的实际最小运行频率
    unsigned long   m_cpuinfoMaxFrequency;        //  硬件读取的实际最大运行频率
    unsigned long   m_cpuinfoCurFrequency;        //  硬件读取的实际当前运行频率

    QList<struct cpufreq_available_frequencies>   m_availableFrequencies;       //  可用的CPU频率值
    QList<struct cpufreq_available_governors>     m_availableGovernors;         //  可用的CPU频率调节器
    struct cpufreq_policy                         m_curPolicy;                  //  当前使用的cpufreq
};

#endif // CPUFREQ_H
