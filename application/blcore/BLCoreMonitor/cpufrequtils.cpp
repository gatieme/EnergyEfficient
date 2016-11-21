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



unsigned long CpuFreqUtils::CpuNumKernel( )
{
    return this->m_cpuNumKernel;
}

unsigned long CpuFreqUtils::CpuNumAvaliable( )
{
    return this->m_cpuNumAvaliable;
}



