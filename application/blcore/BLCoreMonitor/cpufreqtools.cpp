#include "cpufreqtools.h"



/*static*/CpuFreqTools* CpuFreqTools::m_singleton = new CpuFreqTools( );
/*static*/CpuFreqTools::GC CpuFreqTools::GC::gc;


CpuFreqTools::CpuFreqTools(QObject *parent) :
    QObject(parent)
{
    this->m_cpuNumKernel = get_nprocs();
    this->m_cpuNumAvailable = get_nprocs_conf( );
    qDebug() <<"cpu numbers kernel = " <<this->m_cpuNumKernel <<endl;
    qDebug() <<"cpu numbers avaliable = " <<this->m_cpuNumKernel <<endl;
    qDebug() <<"cpu numbers offline = " <<this->m_cpuNumKernel - this->m_cpuNumKernel <<endl;

    for(int cpuid = 0, availCount = 0;
        cpuid < this->m_cpuNumKernel;
        cpuid++)
    {
        //  查看编号为cpuid的CPU是否在线
        if(CpuFreqTools::IsCpuPresent(cpuid) == true)
        {
            availCount++;
            CpuFreqUtils *cpufreq = new CpuFreqUtils(this, cpuid);
            this->m_cpufreqs.append(cpufreq);
            qDebug( ) <<*cpufreq <<endl;
        }
        else
        {
            this->m_cpufreqs.append(NULL);
        }
    }
}



CpuFreqTools::~CpuFreqTools( )
{
    for(int cpuid = 0;
        cpuid < this->m_cpuNumKernel;
        cpuid++)
    {
        CpuFreqUtils *cpufreq = this->m_cpufreqs[cpuid];
        if(cpufreq != NULL)
        {
            delete cpufreq;
        }
    }
}

//  判断编号为cpuid的CPU是否被安装(exist|present)
bool CpuFreqTools::IsCpuPresent(unsigned int cpuid)
{
    if(cpufreq_cpu_exists(cpuid) == 0)
    {
        qDebug() <<"cpu " <<cpuid <<" is present"<<endl;
        return true;
    }
    else
    {
        qDebug() <<"cpu " <<cpuid <<" is not present"<<endl;
        return false;
    }
}


//  判断编号为cpuid的CPU是否活跃(online)
bool CpuFreqTools::IsCpuOnline(unsigned int copuid)
{
    //// NOP
    ///  未实现
    //// NOP
    return true;
}



///////////////////////////////////////////////////////////////////
/// 1--CPU数目的操作
///////////////////////////////////////////////////////////////////

/////////////////////
///  1.1--获取CPU的数目
/////////////////////

/// 获取当前系统中安装的CPU的数目
unsigned long CpuFreqTools::GetCpuNumKernel( )
{
    return this->m_cpuNumKernel;
}

/// 获取当前系统中当前活跃的CPU数目
unsigned long CpuFreqTools::GetCpuNumAvaliable( )
{
    return this->m_cpuNumAvailable;
}


/////////////////////
///  1.2--更新CPU的数目
/////////////////////
/// 更新当前系统中安装的CPU的数目
unsigned long CpuFreqTools::UpdateCpuNumKernel( )
{
    this->m_cpuNumKernel = get_nprocs();

    return this->m_cpuNumKernel;
}

/// 更新当前系统中当前活跃的CPU数目
unsigned long CpuFreqTools::UpdateCpuNumAvaliable( )
{
    this->m_cpuNumAvailable = get_nprocs_conf( );

    return this->m_cpuNumAvailable;
}

/////////////////////
///  1.3--设置CPU的数目
/////////////////////

//  NOP
//  暂时未实现
//  预计实现功能, CPU的热插拔等


///////////////////////////////////////////////////////////////////
/// 2--CPU信息CpuFreq的操作
///////////////////////////////////////////////////////////////////
/////////////////////
//  2.1--获取编号为cpuid的CPU的信息
/////////////////////

//  获取编号为cpuid的CPU完整信息
CpuFreqUtils* CpuFreqTools::GetCpuInfo(unsigned int cpuid)
{
    return this->m_cpufreqs[cpuid];
}

//  编号为cpuid的CPU是否online
const bool CpuFreqTools::GetIsOnline(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetIsOnline( );
}


//  编号为cpuid的CPU的最小运行频率
const unsigned long CpuFreqTools::GetScalingMinFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetScalingMinFrequency( );
}


//  编号为cpuid的CPU的最大运行频率
const unsigned long CpuFreqTools::GetScalingMaxFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetScalingMaxFrequency( );
}


//  编号为cpuid的CPU的当前运行频率
const unsigned long CpuFreqTools::GetScalingCurFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetScalingCurFrequency( );
}


//  编号为cpuid的CPU的最小运行频率
const unsigned long CpuFreqTools::GetCpuInfoMinFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetCpuInfoMinFrequency( );
}

//  编号为cpuid的CPU的最大运行频率
const unsigned long CpuFreqTools::GetCpuInfoMaxFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetCpuInfoMaxFrequency( );
}

//  编号为cpuid的CPU的当前运行频率
const unsigned long CpuFreqTools::GetCpuInfoCurFrequency(unsigned int cpuid)
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
CpuFreqTools::GetAvailableFrequencies(unsigned int cpuid)
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
CpuFreqTools::GetAvailableGovernors(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetAvailableGovernors( );
}



const struct cpufreq_policy*
CpuFreqTools::GetCpuFreqPolicy(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetCpuFreqPolicy( );
}

/////////////////////
//  2.2--更新编号为cpuid的CPU的信息
/////////////////////


//  获取编号为cpuid的CPU完整信息
CpuFreqUtils* CpuFreqTools::UpdateCpuInfo(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateCpuInfo( );
}


//  编号为cpuid的CPU是否online
bool CpuFreqTools::UpdateIsOnline(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateIsOnline( );
}

//  编号为cpuid的CPU的最小运行频率
unsigned long CpuFreqTools::UpdateScalingMinFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateScalingMinFrequency( );
}

//  编号为cpuid的CPU的最大运行频率
unsigned long CpuFreqTools::UpdateScalingMaxFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateScalingMaxFrequency( );
}

//  编号为cpuid的CPU的当前运行频率
unsigned long CpuFreqTools::UpdateScalingCurFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateScalingCurFrequency( );
}


//  编号为cpuid的CPU的最小运行频率
unsigned long CpuFreqTools::UpdateInfoMinFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateCpuInfoMinFrequency( );
}

//  编号为cpuid的CPU的最大运行频率
unsigned long CpuFreqTools::UpdateCpuInfoMaxFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateCpuInfoMaxFrequency( );
}


//  编号为cpuid的CPU的当前运行频率
unsigned long CpuFreqTools::UpdateCpuInfoCurFrequency(unsigned int cpuid)
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
CpuFreqTools::UpdateAvailableFrequencies(unsigned int cpuid)
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
CpuFreqTools::UpdateAvailableGovernors(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateAvailableGovernors( );
}



struct cpufreq_policy*   CpuFreqTools::UpdateCpuFreqPolicy(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateCpuFreqPolicy( );
}


/////////////////////
//  2.3--设置编号为cpuid的CPU的信息
/////////////////////
bool CpuFreqTools::SetPolicy(unsigned int cpuid, struct cpufreq_policy *policy)
{
    return this->GetCpuInfo(cpuid)->SetPolicy(policy);
}


bool CpuFreqTools::SetPolicyMin(unsigned int cpuid, unsigned long minFreq)
{
    return this->GetCpuInfo(cpuid)->SetPolicyMin(minFreq);
}


bool CpuFreqTools::SetPolicyMax(unsigned int cpuid, unsigned long maxFreq)
{
    return this->GetCpuInfo(cpuid)->SetPolicyMax(maxFreq);
}


bool CpuFreqTools::SetPolicyGovernor(unsigned int cpuid, QString *governor)
{
    return this->GetCpuInfo(cpuid)->SetPolicyGovernor(governor);
}


bool CpuFreqTools::SetFrequency(unsigned int cpuid, unsigned long targetFrequency)
{
    return this->GetCpuInfo(cpuid)->SetFrequency(targetFrequency);
}




///////////////////////////////////////////////////////////////////
/// 3--CPU信息CpuUsage的操作
///////////////////////////////////////////////////////////////////
//  获取编号为cpuid的CPU的usage信息
double UpdateCpuUsage(unsigned int cpuid)
{

}


//  获取系统中总的cpuusage信息
double UpdateTotalUsage( )
{


}
