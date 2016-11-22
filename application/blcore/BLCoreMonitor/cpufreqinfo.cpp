#include "cpufreqinfo.h"



/*
unsigned int    m_cpuid;                      //  当前CPU的编号
bool            m_isonline;                   //  当前CPU是否在线

unsigned long   m_scalingMinFrequency;        //  理论上最小运行频率
unsigned long   m_scalingMaxFrequency;        //  理论上最大运行频率
unsigned long   m_scalingCurFrequency;        //  理论上当前运行频率

unsigned long   m_cpuinfoMinFrequency;        //  硬件读取的实际最小运行频率
unsigned long   m_cpuinfoMaxFrequency;        //  硬件读取的实际最大运行频率
unsigned long   m_cpuinfoCurFrequency;        //  硬件读取的实际当前运行频率

QList<struct cpufreq_available_frequencies>   m_availableFrequencies;       //  可用的CPU频率值
QList<struct cpufreq_available_governors>     m_availableGovernors;         //  可用的CPU频率调节器
*/


CpuFreqInfo::CpuFreqInfo(QObject *parent) :
QObject(parent)
{
}


///////////////////////////////////////////////////////////////////
/// CPU信息CpuFreq的操作
///////////////////////////////////////////////////////////////////


/////////////////////
//  获取编号为cpuid的CPU的信息
/////////////////////

//  获取编号为cpuid的CPU完整信息
const CpuFreqInfo CpuFreqInfo::GetCpuInfo( )
{
    return (*this);
}

//  编号为cpuid的CPU是否online
const bool CpuFreqInfo::GetIsOnline( )
{
    return this->m_isonline;
}

//  当前cpu完成频率切换所需要的时间
const unsigned long CpuFreqInfo::GetTransitionLatency( )
{
    return this->m_transitionLatency;
}


//  编号为cpuid的CPU的最小运行频率
const unsigned long CpuFreqInfo::GetScalingMinFrequency( )
{
    assert(this->m_scalingMinFrequency == this->m_curPolicy->min)

    return this->m_cpuinfoMinFrequency;
}

//  编号为cpuid的CPU的最大运行频率
const unsigned long CpuFreqInfo::GetScalingMaxFrequency( )
{
    assert(this->m_scalingMaxFrequency == this->m_curPolicy->max)

    return this->m_scalingMaxFrequency;
}

//  编号为cpuid的CPU的当前运行频率
const unsigned long CpuFreqInfo::GetScalingCurFrequency( )
{
    return this->m_scalingCurFrequency;
}

//  编号为cpuid的CPU的最小运行频率
const unsigned long CpuFreqInfo::GetCpuInfoMinFrequency( )
{
    return this->m_cpuinfoMinFrequency;
}

//  编号为cpuid的CPU的最大运行频率
const unsigned long CpuFreqInfo::GetCpuInfoMaxFrequency( )
{
    return this->m_cpuinfoMaxFrequency;
}


//  编号为cpuid的CPU的当前运行频率
const unsigned long CpuFreqInfo::GetCpuInfoCurFrequency( )
{
    return this->m_scalingCurFrequency;
}


//  可用的CPU频率值
const QList<struct cpufreq_available_frequencies> CpuFreqInfo::GetAvailableFrequencies( )
{
    return this->m_availableFrequencies;
}

//  可用的CPU频率调节器
const QList<struct cpufreq_available_governors> CpuFreqInfo::GetAvailableGovernors( )
{
    return this->m_availableGovernors;
}

const struct cpufreq_policy*   CpuFreqInfo::GetCpuFreqPolicy( )
{
    return this->m_curPolicy;
}





/////////////////////
//  更新编号为cpuid的CPU的信息
/////////////////////

//  获取编号为cpuid的CPU完整信息
const CpuFreqInfo CpuFreqInfo::UpdateCpuInfo( )
{
    this->UpdateIsOnline( );            //  当前CPU是否在线
    this->UpdateTransitionLatency( );   //  当前CPU的调频周期
    this->UpdateCpuFreqPolicy( );       //  当前CPU的调频策略, 包括min, max和governor
    this->UpdateCpuInfoMinFrequency( ); //  从硬件中读取的当前CPU的最小运行频率
    this->UpdateCpuInfoMaxFrequency( ); //  从硬件中读取的当前CPU的最大运行频率
    this->UpdateCpuInfoCurFrequency( ); //  从硬件中读取的当前CPU的运行频率
}

//  编号为cpuid的CPU是否online
bool CpuFreqInfo::UpdateIsOnline( )
{
    if(cpufreq_cpu_exists(this->m_cpuid) == 0)
    {
        this->m_isonline = true;
    }
    else
    {
        this->m_isonline = false;
    }
}


//  当前cpu完成频率切换所需要的时间
const unsigned long CpuFreqInfo::UpdateTransitionLatency( )
{
    unsigned long transitionLatency = cpufreq_get_transition_latency(this->m_cpuid);
    if(transitionLatency == 0)
    {
        qDebug() <<<__FILE__ <<<__LINE__ <<"read transition_latency error" <<endl;
        return -1;
    }
    else
    {
        this->m_transitionLatency = transitionLatency;
        return this->m_transitionLatency;
    }
}

struct cpufreq_policy*   CpuFreqInfo::UpdateCpuFreqPolicy( )
{
    if(this->m_curPolicy != NULL)
    {
        /*  Remember to call cpufreq_put_policy when no longer needed
         *  to avoid memory leakage, please.    */
        cpufreq_put_policy(this->m_curPolicy);
        assert(this->m_curPolicy == NULL);
    }
    struct cpufreq_policy *policy = cpufreq_get_policy(this->cpuid);
    if(policy == NULL)
    {
        qDebug() <<<__FILE__ <<<__LINE__ <<<__func__ <<" error" <<endl;
        return -1;
    }
    else
    {
        this->m_curPolicy = policy;
        this->m_scalingMinFrequency = policy->min;
        this->m_scalingMaxFrequency = policy->max;
        return this->m_curpolicy;
    }
}

//  编号为cpuid的CPU的最小运行频率
unsigned long CpuFreqInfo::UpdateScalingMinFrequency( )
{
    if(this->m_curPolicy != NULL)
    {
        /*  Remember to call cpufreq_put_policy when no longer needed
         *  to avoid memory leakage, please.    */
        cpufreq_put_policy(this->m_curPolicy);
        assert(this->m_curPolicy == NULL);
    }
    struct cpufreq_policy *policy = cpufreq_get_policy(this->cpuid);
    if(policy == NULL)
    {
        qDebug() <<<__FILE__ <<<__LINE__ <<<__func__ <<" error" <<endl;
        return -1;
    }
    else
    {
        this->m_curPolicy = policy;
        this->m_scalingMinFrequency = policy->min;
        this->m_scalingMaxFrequency = policy->max;
        return this->m_scalingMinFrequency;
    }
}

//  编号为cpuid的CPU的最大运行频率
unsigned long CpuFreqInfo::UpdateScalingMaxFrequency( )
{
    if(this->m_curPolicy != NULL)
    {
        /*  Remember to call cpufreq_put_policy when no longer needed
         *  to avoid memory leakage, please.    */
        cpufreq_put_policy(this->m_curPolicy);
        assert(this->m_curPolicy == NULL);
    }
    struct cpufreq_policy *policy = cpufreq_get_policy(this->cpuid);
    if(policy == NULL)
    {
        qDebug() <<<__FILE__ <<<__LINE__ <<<__func__ <<" error" <<endl;
        return -1;
    }
    else
    {
        this->m_curPolicy = policy;
        this->m_scalingMinFrequency = policy->min;
        this->m_scalingMaxFrequency = policy->max;
        return this->m_scalingMaxFrequency;
    }
}


//  编号为cpuid的CPU的当前运行频率
unsigned long CpuFreqInfo::UpdateScalingCurFrequency( )
{
    unsigned long curfreq = cpufreq_get_freq_kernel(this->m_cpuid);

    if(curfreq == 0)
    {
        qDebug() <<<__FILE__ <<<__LINE__ <<"read scaling_cur_freq error" <<endl;
        return -1;
    }
    else
    {
        this->m_scalingCurFrequency = curfreq;
        return m_scalingCurFrequency;
    }
}


//  编号为cpuid的CPU的最小运行频率
unsigned long CpuFreqInfo::UpdateCpuInfoMinFrequency( )
{
    unsigned long min, max;

    if(cpufreq_get_hardware_limits(this->m_cpuid, &min, &max) != 0)
    {
        qDebug() <<<__FILE__ <<<__LINE__ <<"read cpuinfo_min_freq error" <<endl;
        return -1;
    }
    else
    {
        this->m_cpuinfoMinFrequency = min;
        this->m_cpuinfoMaxFrequency = max;
        return this->m_cpuinfoMinFrequency;
    }
}

//  编号为cpuid的CPU的最大运行频率
unsigned long CpuFreqInfo::UpdateCpuInfoMaxFrequency( )
{
    unsigned long min, max;

    if(cpufreq_get_hardware_limits(this->m_cpuid, &min, &max) != 0)
    {
        qDebug() <<<__FILE__ <<<__LINE__ <<"read cpuinfo_max_freq error" <<endl;
        return -1;
    }
    else
    {
        this->m_cpuinfoMinFrequency = min;
        this->m_cpuinfoMaxFrequency = max;
        return this->m_cpuinfoMaxFrequency;
    }
}


//  编号为cpuid的CPU的当前运行频率
unsigned long CpuFreqInfo::UpdateCpuInfoCurFrequency( )
{
    unsigned long curfreq = cpufreq_get_freq_hardware(this->m_cpuid);

    if(curfreq == 0)
    {
        qDebug() <<<__FILE__ <<<__LINE__ <<"read cpuinfo_cur_freq error" <<endl;
        return -1;
    }
    else
    {
        this->m_cpuinfoCurFrequency = curfreq;
        return m_cpuinfoCurFrequency;
    }
}


//  可用的CPU频率值
QList<struct cpufreq_available_frequencies> CpuFreqInfo::UpdateAvailableFrequencies( )
{

}

//  可用的CPU频率调节器
QList<struct cpufreq_available_governors> CpuFreqInfo::UpdateAvailableGovernors( )
{

}

