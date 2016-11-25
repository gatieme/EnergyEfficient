#include "cpuutiltools.h"



#if defined(SINGLETON_GC)

/*static*/CpuUtilTools* CpuUtilTools::m_singleton = new CpuUtilTools( );
/*static*/CpuUtilTools::GC CpuUtilTools::GC::gc;

#elif defined(SINGLETON_NONGC)

/*static*/CpuUtilTools* CpuUtilTools::m_singleton = new CpuUtilTools( );

#endif

CpuUtilTools::CpuUtilTools(QObject *parent) :
    QObject(parent)
{

    this->m_cpuNumKernel = get_nprocs();
    this->m_cpuNumAvailable = get_nprocs_conf( );
    qDebug() <<"cpu numbers kernel = " <<this->m_cpuNumKernel <<endl;
    qDebug() <<"cpu numbers avaliable = " <<this->m_cpuNumKernel <<endl;
    qDebug() <<"cpu numbers offline = " <<this->m_cpuNumKernel - this->m_cpuNumKernel <<endl;

#ifdef CPU_FREQ
    for(int cpuid = 0, availCount = 0;
        cpuid < this->m_cpuNumKernel;
        cpuid++)
    {
        //  查看编号为cpuid的CPU是否在线
        if(CpuUtilTools::IsCpuPresent(cpuid) == true)
        {
            availCount++;
            CpuFreqUtils *cpufrequtil = new CpuFreqUtils(this, cpuid);
            this->m_cpufreqUtils.append(cpufrequtil);
            qDebug( ) <<*cpufrequtil <<endl;
        }
        else
        {
            this->m_cpufreqUtils.append(NULL);
        }
    }
#endif

#ifdef CPU_USAGE
    this->m_cpuusages = new CpuUsageUtils(this, this->m_cpuNumKernel);
#endif
}



CpuUtilTools::~CpuUtilTools( )
{
#ifdef CPU_FREQ
    for(int cpuid = 0;
        cpuid < this->m_cpuNumKernel;
        cpuid++)
    {
        CpuFreqUtils *cpufreq = this->m_cpufreqUtils[cpuid];
        if(cpufreq != NULL)
        {
            delete cpufreq;
        }
    }
#endif
}





///////////////////////////////////////////////////////////////////
/// 1--CPU数目的操作
///////////////////////////////////////////////////////////////////

/////////////////////
///  1.1--获取CPU的数目
/////////////////////

/// 获取当前系统中安装的CPU的数目
unsigned long CpuUtilTools::GetCpuNumKernel( )
{
    return this->m_cpuNumKernel;
}

/// 获取当前系统中当前活跃的CPU数目
unsigned long CpuUtilTools::GetCpuNumAvaliable( )
{
    return this->m_cpuNumAvailable;
}


/////////////////////
///  1.2--更新CPU的数目
/////////////////////
/// 更新当前系统中安装的CPU的数目
unsigned long CpuUtilTools::UpdateCpuNumKernel( )
{
    this->m_cpuNumKernel = get_nprocs();

    return this->m_cpuNumKernel;
}

/// 更新当前系统中当前活跃的CPU数目
unsigned long CpuUtilTools::UpdateCpuNumAvaliable( )
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



#ifdef CPU_FREQ
//  判断编号为cpuid的CPU是否被安装(exist|present)
bool CpuUtilTools::IsCpuPresent(unsigned int cpuid)
{
    if(cpufreq_cpu_exists(cpuid) == 0)
    {
        //qDebug() <<"cpu " <<cpuid <<" is present"<<endl;
        return true;
    }
    else
    {
        qDebug() <<"cpu " <<cpuid <<" is not present"<<endl;
        return false;
    }
}


//  判断编号为cpuid的CPU是否活跃(online)
bool CpuUtilTools::IsCpuOnline(unsigned int copuid)
{
    //// NOP
    ///  未实现
    //// NOP
    return true;
}




///////////////////////////////////////////////////////////////////
/// 2--CPU信息CpuFreq的操作
///////////////////////////////////////////////////////////////////
/////////////////////
//  2.1--获取编号为cpuid的CPU的信息
/////////////////////

//  获取编号为cpuid的CPU完整信息
CpuFreqUtils* CpuUtilTools::GetCpuInfo(unsigned int cpuid)
{
    return this->m_cpufreqUtils[cpuid];
}

//  编号为cpuid的CPU是否online
const bool CpuUtilTools::GetIsOnline(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetIsOnline( );
}


//  编号为cpuid的CPU的最小运行频率
const unsigned long CpuUtilTools::GetScalingMinFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetScalingMinFrequency( );
}


//  编号为cpuid的CPU的最大运行频率
const unsigned long CpuUtilTools::GetScalingMaxFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetScalingMaxFrequency( );
}


//  编号为cpuid的CPU的当前运行频率
const unsigned long CpuUtilTools::GetScalingCurFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetScalingCurFrequency( );
}


//  编号为cpuid的CPU的最小运行频率
const unsigned long CpuUtilTools::GetCpuInfoMinFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetCpuInfoMinFrequency( );
}

//  编号为cpuid的CPU的最大运行频率
const unsigned long CpuUtilTools::GetCpuInfoMaxFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetCpuInfoMaxFrequency( );
}

//  编号为cpuid的CPU的当前运行频率
const unsigned long CpuUtilTools::GetCpuInfoCurFrequency(unsigned int cpuid)
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
CpuUtilTools::GetAvailableFrequencies(unsigned int cpuid)
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
CpuUtilTools::GetAvailableGovernors(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetAvailableGovernors( );
}



const struct cpufreq_policy*
CpuUtilTools::GetCpuFreqPolicy(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->GetCpuFreqPolicy( );
}

/////////////////////
//  2.2--更新编号为cpuid的CPU的信息
/////////////////////


//  获取编号为cpuid的CPU完整信息
CpuFreqUtils* CpuUtilTools::UpdateCpuInfo(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateCpuInfo( );
}


//  编号为cpuid的CPU是否online
bool CpuUtilTools::UpdateIsOnline(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateIsOnline( );
}

//  编号为cpuid的CPU的最小运行频率
unsigned long CpuUtilTools::UpdateScalingMinFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateScalingMinFrequency( );
}

//  编号为cpuid的CPU的最大运行频率
unsigned long CpuUtilTools::UpdateScalingMaxFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateScalingMaxFrequency( );
}

//  编号为cpuid的CPU的当前运行频率
unsigned long CpuUtilTools::UpdateScalingCurFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateScalingCurFrequency( );
}


//  编号为cpuid的CPU的最小运行频率
unsigned long CpuUtilTools::UpdateInfoMinFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateCpuInfoMinFrequency( );
}

//  编号为cpuid的CPU的最大运行频率
unsigned long CpuUtilTools::UpdateCpuInfoMaxFrequency(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateCpuInfoMaxFrequency( );
}


//  编号为cpuid的CPU的当前运行频率
unsigned long CpuUtilTools::UpdateCpuInfoCurFrequency(unsigned int cpuid)
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
CpuUtilTools::UpdateAvailableFrequencies(unsigned int cpuid)
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
CpuUtilTools::UpdateAvailableGovernors(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateAvailableGovernors( );
}



struct cpufreq_policy*   CpuUtilTools::UpdateCpuFreqPolicy(unsigned int cpuid)
{
    return this->GetCpuInfo(cpuid)->UpdateCpuFreqPolicy( );
}


/////////////////////
//  2.3--设置编号为cpuid的CPU的信息
/////////////////////
bool CpuUtilTools::SetPolicy(unsigned int cpuid, struct cpufreq_policy *policy)
{
    return this->GetCpuInfo(cpuid)->SetPolicy(policy);
}


bool CpuUtilTools::SetPolicyMin(unsigned int cpuid, unsigned long minFreq)
{
    return this->GetCpuInfo(cpuid)->SetPolicyMin(minFreq);
}


bool CpuUtilTools::SetPolicyMax(unsigned int cpuid, unsigned long maxFreq)
{
    return this->GetCpuInfo(cpuid)->SetPolicyMax(maxFreq);
}


bool CpuUtilTools::SetPolicyGovernor(unsigned int cpuid, QString *governor)
{
    return this->GetCpuInfo(cpuid)->SetPolicyGovernor(governor);
}


bool CpuUtilTools::SetFrequency(unsigned int cpuid, unsigned long targetFrequency)
{
    return this->GetCpuInfo(cpuid)->SetFrequency(targetFrequency);
}

#endif


#ifdef CPU_USAGE


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

#endif

///////////////////////////////////////////////////////////////////
/// 3--CPU
///////////////////////////////////////////////////////////////////
/////////////////////
//  3.1--获取编号为cpuid的CPU-freq的信息
/////////////////////
//  CPU的当前运行频率
QList<unsigned long> CpuUtilTools::UpdateAllCpusScalingCurFrequency( )
{
#ifdef CPU_FREQ
    for(int cpuid = 0, availCount = 0;
        cpuid < this->m_cpuNumKernel;
        cpuid++)
    {
        //  查看编号为cpuid的CPU是否在线
        if(CpuUtilTools::IsCpuPresent(cpuid) == true)
        {
            availCount++;
            double cpufreq = this->m_cpufreqUtils[cpuid]->UpdateScalingCurFrequency( );
            this->m_cpufreqs.append(cpufreq);
        }
    }
#else
    qDebug( ) <<__FILE__ <<", " <<__LINE__ <<endl;
#endif
    return this->m_cpufreqs;
}


//  当前运行频率
QList<unsigned long> CpuUtilTools::UpdateAllCpusCpuInfoCurFrequency( )
{

}


/////////////////////
//  3.2--获取编号为cpuid的CPU-usage的信息
/////////////////////
QList<double> CpuUtilTools::UpdateAllCpusUsage( )
{
#ifdef CPU_USAGE
    //qDebug( ) <<__FILE__ <<", " <<__LINE__ <<endl;
    return this->m_cpuusages->UpdateAllCpusUsage( );
    //qDebug( ) <<__FILE__ <<", " <<__LINE__ <<endl;
#else
    qDebug( ) <<__FILE__ <<", " <<__LINE__ <<endl;
#endif
}



