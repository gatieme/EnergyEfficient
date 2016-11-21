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
const CpuFreqInfo GetCpuInfo(unsigned int cpuid)
{

}

//  编号为cpuid的CPU是否online
const bool GetIsOnline(unsigned int cpuid)
{

}


//  编号为cpuid的CPU的最小运行频率
const unsigned long GetScalingMinFrequency(unsigned int cpuid)
{

}


//  编号为cpuid的CPU的最大运行频率
const unsigned long GetScalingMaxFrequency(unsigned int cpuid)
{

}


//  编号为cpuid的CPU的当前运行频率
const unsigned long GetScalingCurFrequency(unsigned int cpuid)
{

}


//  编号为cpuid的CPU的最小运行频率
const unsigned long GetCpuInfoMinFrequency(unsigned int cpuid)
{

}

//  编号为cpuid的CPU的最大运行频率
const unsigned long GetCpuInfoMaxFrequency(unsigned int cpuid)
{

}

//  编号为cpuid的CPU的当前运行频率
const unsigned long GetCpuInfoCurFrequency(unsigned int cpuid)
{

}



//  可用的CPU频率值
const QList<struct cpufreq_available_frequencies> GetAvailableFrequencies(unsigned int cpuid)
{

}


//  可用的CPU频率调节器
const QList<struct cpufreq_available_governors> GetAvailableGovernors(unsigned int cpuid)
{

}

const struct cpufreq_policy   GetCpuFreqPolicy(unsigned int cpuid)
{

}

/////////////////////
//  更新编号为cpuid的CPU的信息
/////////////////////


//  获取编号为cpuid的CPU完整信息
const CpuFreqInfo UpdateCpuInfo(unsigned int cpuid)
{

}


//  编号为cpuid的CPU是否online
const bool UpdateIsOnline(unsigned int cpuid)
{

}

//  编号为cpuid的CPU的最小运行频率
unsigned long UpdateScalingMinFrequency(unsigned int cpuid)
{

}

//  编号为cpuid的CPU的最大运行频率
unsigned long UpdateScalingMaxFrequency(unsigned int cpuid)
{

}

//  编号为cpuid的CPU的当前运行频率
unsigned long UpdateScalingCurFrequency(unsigned int cpuid)
{

}


//  编号为cpuid的CPU的最小运行频率
unsigned long UpdateInfoMinFrequency(unsigned int cpuid)
{

}

//  编号为cpuid的CPU的最大运行频率
unsigned long UpdateCpuInfoMaxFrequency(unsigned int cpuid)
{

}


//  编号为cpuid的CPU的当前运行频率
unsigned long UpdateCpuInfoCurFrequency(unsigned int cpuid)
{

}

//  可用的CPU频率值
QList<struct cpufreq_available_frequencies> UpdateAvailableFrequencies(unsigned int cpuid)
{

}

//  可用的CPU频率调节器
QList<struct cpufreq_available_governors> UpdateAvailableGovernors(unsigned int cpuid)
{

}

struct cpufreq_policy   UpdateCpuFreqPolicy(unsigned int cpuid)
{

}



