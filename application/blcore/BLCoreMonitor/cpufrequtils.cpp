#include "cpufrequtils.h"



/*static*/CpuFreqUtils* CpuFreqUtils::m_singleton = new CpuFreqUtils( );
/*static*/CpuFreqUtils::GC CpuFreqUtils::GC::gc;


CpuFreqUtils::CpuFreqUtils(QObject *parent) :
    QObject(parent)
{
    this->m_cpuNumKernel = get_nprocs();
    this->m_cpuNumAvaliable = get_nprocs_conf( );
    qDebug() <<"cpu numbers kernel = " <<this->m_cpuNumKernel <<endl;
    qDebug() <<"cpu numbers avaliable = " <<this->m_cpuNumKernel <<endl;
    qDebug() <<"cpu numbers offline = " <<this->m_cpuNumKernel - this->m_cpuNumKernel <<endl;
}

///////////////////////////////////////////////////////////////////
/// CPU数目的操作
///////////////////////////////////////////////////////////////////

/////////////////////
///  获取CPU的数目
/////////////////////

/// 获取当前系统中安装的CPU的数目
unsigned long CpuFreqUtils::GetCpuNumKernel( )
{
    return this->m_cpuNumKernel;
}

/// 获取当前系统中当前活跃的CPU数目
unsigned long CpuFreqUtils::GetCpuNumAvaliable( )
{
    return this->m_cpuNumAvaliable;
}


/////////////////////
///  更新CPU的数目
/////////////////////
/// 更新当前系统中安装的CPU的数目
unsigned long CpuFreqUtils::UpdateCpuNumKernel( )
{
    this->m_cpuNumKernel = get_nprocs();

    return this->m_cpuNumKernel;
}

/// 更新当前系统中当前活跃的CPU数目
unsigned long CpuFreqUtils::UpdateCpuNumAvaliable( )
{
    this->m_cpuNumAvaliable = get_nprocs_conf( );

    return this->m_cpuNumAvaliable;
}

/////////////////////
///  设置CPU的数目
/////////////////////

//  NOP
//  暂时未实现
//  预计实现功能, CPU的热插拔等


///////////////////////////////////////////////////////////////////
/// CPU信息CpuFreq的操作
///////////////////////////////////////////////////////////////////
/////////////////////
//  获取编号为cpuid的CPU的信息
/////////////////////

//  获取编号为cpuid的CPU完整信息
CpuFreqInfo* CpuFreqUtils::GetCpuInfo(unsigned int cpuid)
{
    return this->m_cpus[cpuid];
}

//  编号为cpuid的CPU是否online
const bool CpuFreqUtils::GetIsOnline(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetIsOnline( );
}


//  编号为cpuid的CPU的最小运行频率
const unsigned long CpuFreqUtils::GetScalingMinFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetScalingMinFrequency( );
}


//  编号为cpuid的CPU的最大运行频率
const unsigned long CpuFreqUtils::GetScalingMaxFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetScalingMaxFrequency( );
}


//  编号为cpuid的CPU的当前运行频率
const unsigned long CpuFreqUtils::GetScalingCurFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetScalingCurFrequency( );
}


//  编号为cpuid的CPU的最小运行频率
const unsigned long CpuFreqUtils::GetCpuInfoMinFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetCpuInfoMinFrequency( );
}

//  编号为cpuid的CPU的最大运行频率
const unsigned long CpuFreqUtils::GetCpuInfoMaxFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetCpuInfoMaxFrequency( );
}

//  编号为cpuid的CPU的当前运行频率
const unsigned long CpuFreqUtils::GetCpuInfoCurFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetCpuInfoCurFrequency( );
}



//  可用的CPU频率值
#if defined(CNODE_IN_QLIST)
//一种是将节点重新组织在QList中
QList<struct cpufreq_available_frequencies *>&
#elif defined(CLIST_TO_QLIST)
//另一种是近将节点的数据域组织在QList, 即将CLIST转换为QLIST
QList<QString>&                                      //  可用的CPU频率值
#elif defined(USE_CLIST)
//另外一种方式是直接使用CLIST
struct cpufreq_available_frequencies*            //  可用的CPU频率值
#endif
CpuFreqUtils::GetAvailableFrequencies(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetAvailableFrequencies( );
}


//  可用的CPU频率值
#if defined(CNODE_IN_QLIST)
//一种是将节点重新组织在QList中
QList<struct cpufreq_available_governors *>&
#elif defined(CLIST_TO_QLIST)
//另一种是近将节点的数据域组织在QList, 即将CLIST转换为QLIST
QList<unsigned long >&                            //  可用的CPU频率调节器
#elif defined(USE_CLIST)
//另外一种方式是直接使用CLIST
struct cpufreq_available_governors *              //  可用的CPU频率调节器
#endif
CpuFreqUtils::GetAvailableGovernors(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetAvailableGovernors( );
}



const struct cpufreq_policy*
CpuFreqUtils::GetCpuFreqPolicy(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetCpuFreqPolicy( );
}

/////////////////////
//  更新编号为cpuid的CPU的信息
/////////////////////


//  获取编号为cpuid的CPU完整信息
CpuFreqInfo* CpuFreqUtils::UpdateCpuInfo(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateCpuInfo( );
}


//  编号为cpuid的CPU是否online
bool CpuFreqUtils::UpdateIsOnline(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateIsOnline( );
}

//  编号为cpuid的CPU的最小运行频率
unsigned long CpuFreqUtils::UpdateScalingMinFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateScalingMinFrequency( );
}

//  编号为cpuid的CPU的最大运行频率
unsigned long CpuFreqUtils::UpdateScalingMaxFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateScalingMaxFrequency( );
}

//  编号为cpuid的CPU的当前运行频率
unsigned long CpuFreqUtils::UpdateScalingCurFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateScalingCurFrequency( );
}


//  编号为cpuid的CPU的最小运行频率
unsigned long CpuFreqUtils::UpdateInfoMinFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateCpuInfoMinFrequency( );
}

//  编号为cpuid的CPU的最大运行频率
unsigned long CpuFreqUtils::UpdateCpuInfoMaxFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateCpuInfoMaxFrequency( );
}


//  编号为cpuid的CPU的当前运行频率
unsigned long CpuFreqUtils::UpdateCpuInfoCurFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateCpuInfoCurFrequency( );
}



//  可用的CPU频率值
#if defined(CNODE_IN_QLIST)
//一种是将节点重新组织在QList中
QList<struct cpufreq_available_frequencies *>&
#elif defined(CLIST_TO_QLIST)
//另一种是近将节点的数据域组织在QList, 即将CLIST转换为QLIST
QList<QString>&                                      //  可用的CPU频率值
#elif defined(USE_CLIST)
//另外一种方式是直接使用CLIST
struct cpufreq_available_frequencies *            //  可用的CPU频率值
#endif
CpuFreqUtils::UpdateAvailableFrequencies(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateAvailableFrequencies( );
}



//  可用的CPU频率值
#if defined(CNODE_IN_QLIST)
//一种是将节点重新组织在QList中
QList<struct cpufreq_available_governors *>&
#elif defined(CLIST_TO_QLIST)
//另一种是近将节点的数据域组织在QList, 即将CLIST转换为QLIST
QList<unsigned long >&                            //  可用的CPU频率调节器
#elif defined(USE_CLIST)
//另外一种方式是直接使用CLIST
struct cpufreq_available_governors *              //  可用的CPU频率调节器
#endif
CpuFreqUtils::UpdateAvailableGovernors(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateAvailableGovernors( );
}



struct cpufreq_policy*   CpuFreqUtils::UpdateCpuFreqPolicy(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateCpuFreqPolicy( );
}



