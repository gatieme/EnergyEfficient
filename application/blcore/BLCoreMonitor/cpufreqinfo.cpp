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
const CpuFreqInfo GetCpuInfo( )      
{

}

//  编号为cpuid的CPU是否online
const bool GetIsOnline( )                  
{

}

//  编号为cpuid的CPU的最小运行频率
const unsigned long GetScalingMinFrequency( )   
{

}

//  编号为cpuid的CPU的最大运行频率
const unsigned long GetScalingMaxFrequency( )   
{

}

//  编号为cpuid的CPU的当前运行频率
const unsigned long GetScalingCurFrequency( )   
{

}

//  编号为cpuid的CPU的最小运行频率
const unsigned long GetCpuInfoMinFrequency( )   
{

}

//  编号为cpuid的CPU的最大运行频率
const unsigned long GetCpuInfoMaxFrequency( )   
{

}


//  编号为cpuid的CPU的当前运行频率
const unsigned long GetCpuInfoCurFrequency( )   
{
}


//  可用的CPU频率值
const QList<struct cpufreq_available_frequencies> GetAvailableFrequencies( )   
{

}

//  可用的CPU频率调节器
const QList<struct cpufreq_available_governors> GetAvailableGovernors( )         
{

}

const struct cpufreq_policy   GetCpuFreqPolicy( )
{

}





/////////////////////
//  更新编号为cpuid的CPU的信息
/////////////////////

//  获取编号为cpuid的CPU完整信息
const CpuFreqInfo UpdateCpuInfo( )      
{

}

//  编号为cpuid的CPU是否online
bool UpdateIsOnline( )                  
{
    
}

//  编号为cpuid的CPU的最小运行频率
unsigned long UpdateScalingMinFrequency( )   
{
    
}

//  编号为cpuid的CPU的最大运行频率
unsigned long UpdateScalingMaxFrequency( )  
{
    
}

//  编号为cpuid的CPU的当前运行频率
unsigned long UpdateScalingCurFrequency( )   
{
    
}


//  编号为cpuid的CPU的最小运行频率
unsigned long UpdateInfoMinFrequency( )   
{
    
}

//  编号为cpuid的CPU的最大运行频率
unsigned long UpdateCpuInfoMaxFrequency( )  
{
    
}


//  编号为cpuid的CPU的当前运行频率

unsigned long UpdateCpuInfoCurFrequency( )   
{    
}



//  可用的CPU频率值
QList<struct cpufreq_available_frequencies> UpdateAvailableFrequencies( )   
{
    
}

//  可用的CPU频率调节器
QList<struct cpufreq_available_governors> UpdateAvailableGovernors( )         
{
    
}

struct cpufreq_policy   UpdateCpuFreqPolicy( )
{
    
}