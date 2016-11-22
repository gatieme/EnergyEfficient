#include "cpufreqinfo.h"

#include <cassert>


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
/// 1--CPU信息CpuFreq的操作
///////////////////////////////////////////////////////////////////


/////////////////////
//  1.1--获取编号为cpuid的CPU的信息
/////////////////////

//  获取编号为cpuid的CPU完整信息
const CpuFreqInfo* CpuFreqInfo::GetCpuInfo( )
{
    return (this);
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


//  当前CPU的调频策略
const struct cpufreq_policy*   CpuFreqInfo::GetCpuFreqPolicy( )
{
    return this->m_curPolicy;
}



//  编号为cpuid的CPU的最小运行频率
const unsigned long CpuFreqInfo::GetScalingMinFrequency( )
{
    assert(this->m_scalingMinFrequency == this->m_curPolicy->min);

    return this->m_scalingMinFrequency;
}

//  编号为cpuid的CPU的最大运行频率
const unsigned long CpuFreqInfo::GetScalingMaxFrequency( )
{
    assert(this->m_scalingMaxFrequency == this->m_curPolicy->max);

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


#if defined(CNODE_IN_QLIST)
//一种是将节点重新组织在QList中
QList<struct cpufreq_available_frequencies *>&
CpuFreqInfo::GetAvailableFrequencies( )   //  可用的CPU频率值
{
    return this->m_avaliableFrequencies;
}

QList<struct cpufreq_available_governors *>&
CpuFreqInfo::GetAvailableGovernors( );         //  可用的CPU频率调节器
{
    return this->m_availableGovernors;
}
#elif defined(CLIST_TO_QLIST)
//另一种是近将节点的数据域组织在QList, 即将CLIST转换为QLIST
QList<QString>&
CpuFreqInfo::GetAvailableFrequencies( )   //  可用的CPU频率值
{
    return this->m_availableFrequencies;
}


QList<unsigned long >&
CpuFreqInfo::GetAvailableGovernors( )         //  可用的CPU频率调节器
{
    return this->m_availableGovernors;
}

#elif defined(USE_CLIST)
//另外一种方式是直接使用CLIST
struct cpufreq_available_frequencies*
CpuFreqInfo::GetAvailableFrequencies( )   //  可用的CPU频率值
{
    return this->m_availableFrequencies;
}

struct cpufreq_available_governors*
CpuFreqInfo::GetAvailableGovernors( )         //  可用的CPU频率调节器
{
    return this->m_availableGovernors;
}

#endif







/////////////////////
//  1.2--更新编号为cpuid的CPU的信息
/////////////////////

//  获取编号为cpuid的CPU完整信息
CpuFreqInfo* CpuFreqInfo::UpdateCpuInfo( )
{
    this->UpdateIsOnline( );            //  当前CPU是否在线
    this->UpdateTransitionLatency( );   //  当前CPU的调频周期
    this->UpdateCpuFreqPolicy( );       //  当前CPU的调频策略, 包括min, max和governor
    this->UpdateCpuInfoMinFrequency( ); //  从硬件中读取的当前CPU的最小运行频率
    this->UpdateCpuInfoMaxFrequency( ); //  从硬件中读取的当前CPU的最大运行频率
    this->UpdateCpuInfoCurFrequency( ); //  从硬件中读取的当前CPU的运行频率

    return (this);
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
unsigned long CpuFreqInfo::UpdateTransitionLatency( )
{
    unsigned long transitionLatency = cpufreq_get_transition_latency(this->m_cpuid);
    if(transitionLatency == 0)
    {
        qDebug() <<__FILE__ <<", " <<__LINE__ <<"read transition_latency error" <<endl;
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
    struct cpufreq_policy *policy = cpufreq_get_policy(this->m_cpuid);
    if(policy == NULL)
    {
        qDebug() <<__FILE__ <<", " <<__LINE__ <<__func__ <<" error" <<endl;
        return NULL;
    }
    else
    {
        this->m_curPolicy = policy;
        this->m_scalingMinFrequency = policy->min;
        this->m_scalingMaxFrequency = policy->max;
        return this->m_curPolicy;
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
    struct cpufreq_policy *policy = cpufreq_get_policy(this->m_cpuid);
    if(policy == NULL)
    {
        qDebug() <<__FILE__ <<", " <<__LINE__ <<__func__ <<" error" <<endl;
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
    struct cpufreq_policy *policy = cpufreq_get_policy(this->m_cpuid);
    if(policy == NULL)
    {
        qDebug() <<__FILE__ <<", " <<__LINE__ <<__func__ <<" error" <<endl;
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
        qDebug() <<__FILE__ <<", " <<__LINE__ <<"read scaling_cur_freq error" <<endl;
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
        qDebug() <<__FILE__ <<", " <<__LINE__ <<"read cpuinfo_min_freq error" <<endl;
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
        qDebug() <<__FILE__ <<", " <<__LINE__ <<"read cpuinfo_max_freq error" <<endl;
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
        qDebug() <<__FILE__ <<", " <<__LINE__ <<"read cpuinfo_cur_freq error" <<endl;
        return -1;
    }
    else
    {
        this->m_cpuinfoCurFrequency = curfreq;
        return m_cpuinfoCurFrequency;
    }
}

#if defined(CNODE_IN_QLIST)

//一种是将节点重新组织在QList中
QList<struct cpufreq_available_frequencies *>&
CpuFreqInfo::UpdateAvailableFrequencies( )   //  可用的CPU频率值
{


}


QList<struct cpufreq_available_governors *>&
CpuFreqInfo::UpdateAvailableGovernors( )         //  可用的CPU频率调节器
{


}



#elif defined(CLIST_TO_QLIST)

//另一种是近将节点的数据域组织在QList, 即将CLIST转换为QLIST
QList<QString>&
CpuFreqInfo::UpdateAvailableFrequencies( )   //  可用的CPU频率值
{

}

QList<unsigned long >&
CpuFreqInfo::UpdateAvailableGovernors( )         //  可用的CPU频率调节器
{

}


#elif defined(USE_CLIST)

//另外一种方式是直接使用CLIST
struct cpufreq_available_frequencies *
CpuFreqInfo::UpdateAvailableFrequencies( )   //  可用的CPU频率值
{
    struct cpufreq_available_frequencies *headFrequencies = cpufreq_get_available_frequencies(this->m_cpuid);
    if(headFrequencies == NULL)
    {
        qDebug() <<__FILE__ <<", " <<__LINE__ <<"read cpufreq_available_frequencies error" <<endl;
        return NULL;
    }
    else
    {
        if(this->m_availableFrequencies != NULL)    //  首先清除原来的数据, 避免内存泄露
        {
            cpufreq_put_available_frequencies(this->m_availableFrequencies);
        }

        this->m_availableFrequencies = headFrequencies;
        return this->m_availableFrequencies;
    }
}


struct cpufreq_available_governors*
CpuFreqInfo::UpdateAvailableGovernors( )         //  可用的CPU频率调节器
{
    struct cpufreq_available_governors *headGovernors = cpufreq_get_available_governors(this->m_cpuid);
    if(headGovernors == NULL)
    {
        qDebug() <<__FILE__ <<", " <<__LINE__ <<"read cpufreq_available_governors error" <<endl;
        return NULL;
    }
    else
    {
        if(this->m_availableGovernors != NULL)    //  首先清除原来的数据, 避免内存泄露
        {
            cpufreq_put_available_governors(this->m_availableGovernors);
        }
        this->m_availableGovernors = headGovernors;
        return this->m_availableGovernors;
    }
}

#endif


/////////////////////
//  1.3--更新当前CPU的信息
/////////////////////
bool CpuFreqInfo::SetPolicy(struct cpufreq_policy *policy)
{
    if(cpufreq_set_policy(this->m_cpuid, policy) != 0)
    {
        qDebug() <<__FILE__ <<", " <<__LINE__ <<" set policy error" <<endl;
        return false;
    }

    return true;
}


bool CpuFreqInfo::SetPolicyMin(unsigned long minFreq)
{
    if(cpufreq_modify_policy_min(this->m_cpuid, minFreq) != 0)
    {
        qDebug() <<__FILE__ <<", " <<__LINE__ <<"set policy min frequency " <<minFreq <<" failed" <<endl;
        return false;
    }

    return true;
}

bool CpuFreqInfo::SetPolicyMax(unsigned long maxFreq)
{
    if(cpufreq_modify_policy_max(this->m_cpuid, maxFreq) != 0)
    {
        qDebug() <<__FILE__ <<", " <<__LINE__ <<"set policy max frequency " <<maxFreq <<" failed" <<endl;
        return false;
    }

    return true;
}


bool CpuFreqInfo::SetPolicyGovernor(QString *governor)
{
    char targetGovernor[81];
    strcpy(targetGovernor, governor->toStdString( ).c_str( ));
    if(cpufreq_modify_policy_governor(this->m_cpuid, targetGovernor) != 0)
    {
        qDebug( ) <<__FILE__ <<", " <<__LINE__ <<" set policy min frequency " <<governor <<" failed" <<endl;
        return false;
    }
    qDebug( ) <<__FILE__ <<", " <<__LINE__ <<" set policy governor to " <<targetGovernor <<" success" <<endl;
    return true;
}


bool CpuFreqInfo::SetFrequency(unsigned long targetFrequency)
{
    if(cpufreq_set_frequency(this->m_cpuid, targetFrequency) != 0)
    {
        qDebug() <<__FILE__ <<", " <<__LINE__ <<"set policy frequency " <<targetFrequency <<" failed" <<endl;
        return false;
    }

    return true;
}

