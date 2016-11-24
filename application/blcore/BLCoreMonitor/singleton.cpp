#include "singleton.h"


Singleton*  Singleton::m_singleton = NULL;



///////////////////////////////////////////////////////////////////
/// 3--CPU
///////////////////////////////////////////////////////////////////
/////////////////////
//  3.1--获取编号为cpuid的CPU-freq的信息
/////////////////////
QList<unsigned long> Singleton::UpdateAllCpusScalingCurFrequency( )   //  CPU的当前运行频率
{

}


QList<unsigned long> Singleton::UpdateAllCpusCpuInfoCurFrequency( )   //  当前运行频率
{

}
/////////////////////
//  3.2--获取编号为cpuid的CPU-usage的信息
/////////////////////

QList<double>  Singleton::UpdateAllCpusUsage( )                 //  当前运行频率
{

}
