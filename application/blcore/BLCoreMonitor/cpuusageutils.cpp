#include "cpuusageutils.h"

CpuUsageUtils::CpuUsageUtils(QObject *parent, unsigned int cpunums) :
    QObject(parent), m_cpunums(cpunums)
{
    if(cpunums > 0)
    {
        this->InitAllCpusJiffiesStat( );
    }

}

unsigned int CpuUsageUtils::InitAllCpusJiffiesStat( )
{
    if(this->m_jiffiesStats.size( ) > 0)
    {
        this->m_jiffiesStats.clear( );
    }
    struct cpuusage_jiffies_stat* jiffies_stat_list = cpuusage_get_jiffies_stat_list();
    struct cpuusage_jiffies_stat* curr_stat = jiffies_stat_list;
    qDebug( ) <<__FILE__ <<", " <<__LINE__ <<sizeof(struct cpuusage_jiffies_stat) <<endl;
    while(curr_stat != NULL)
    {
        //curr_stat->guest_nice = 0;
        this->m_jiffiesStats.append(curr_stat);
        ShowCpuJiffiesStat(curr_stat);

        curr_stat = curr_stat->next;
    }

    return this->m_jiffiesStats.size( );

}



unsigned int CpuUsageUtils::UninitPrevCpusJiffiesStat()
{
    if(this->m_prevJiffiesStats.size( ) == 0 )
    {
        return 0;
    }
    foreach (struct cpuusage_jiffies_stat * stat, this->m_prevJiffiesStats)
    {
        cpuusage_put_jiffies_stat(stat);
    }
    this->m_prevJiffiesStats.clear( );
}

///  保存旧的m_jiffiesStats信息到m_prevJiffiesStats信息
unsigned int CpuUsageUtils::CopyJiffiesStatsToPre( )
{
    if(this->m_prevJiffiesStats.size( ) != 0)
    {
        this->UninitPrevCpusJiffiesStat( );
    }
    else if(this->m_jiffiesStats.size( ) == 0)
    {
        qDebug( ) <<__FILE__ <<", " <<__LINE__ <<", " <<__func__<<" error" <<endl;
    }
    else
    {
        for(int cpuid = 0; cpuid <= this->m_cpunums; cpuid++)
        {
            this->m_prevJiffiesStats.append(this->m_jiffiesStats[cpuid]);
        }
    }
}

/// 计算系统的cpu使用率
QList<double>  CpuUsageUtils::CalcAllCpusUsage( )
{
    double usage;
    if(this->m_cpuusgae.length( ) != 0)
    {
        this->m_cpuusgae.clear( );
    }

    for(int cpuid = 0; cpuid <= this->m_cpunums; cpuid++)
    {
        ShowCpuJiffiesStat(this->m_jiffiesStats[cpuid]);
        ShowCpuJiffiesStat(this->m_prevJiffiesStats[cpuid]);
        //qDebug( ) <<this->m_jiffiesStats[cpuid]->cpu <<endl;
        usage = cpuusage_calc_usage(this->m_prevJiffiesStats[cpuid], this->m_jiffiesStats[cpuid]);
        qDebug( ) <<"cpuid = " <<cpuid <<", cpusuage = " <<usage <<endl;
        this->m_cpuusgae.append(usage);
    }
}

///  输出jiffies stat的值
void CpuUsageUtils::ShowCpuJiffiesStat(cpuusage_jiffies_stat *stat)
{
    qDebug() <<"jiffies-stat : cpu = " <<stat->cpu;
    qDebug() <<stat->user <<", " <<stat->nice <<", "
             <<stat->system <<", " <<stat->idle <<", "
             <<stat->iowait <<", " <<stat->irq <<", "
             <<stat->softirq <<", " <<stat->steal <<", "
             <<stat->guest <<", " <<stat->guest_nice <<endl;
}

///////////////////////////////////////////////////////////////////
/// 1--CPU使用率usage的操作接口
///////////////////////////////////////////////////////////////////

/////////////////////
///  1.1--获取CPU的Jiffies Stat信息
/////////////////////

//  获取编号为cpuid的CPU的jiffies stat信息
struct cpuusage_jiffies_stat *
CpuUsageUtils::GetCpuJiffiesStat(unsigned int cpuid)
{
    return this->m_jiffiesStats[cpuid];
}

//  获取系统中总的CPU jiffies stat信息
struct cpuusage_jiffies_stat *
CpuUsageUtils::GetTotalCpuJiffiesStat( )
{
    return this->m_jiffiesStats[this->m_cpunums];
}

//  获取所有的cpu和总的jiffies stat信息
cpuusage_jiffies_stat_list
CpuUsageUtils::GetAllCpusJiffiesStat( )
{
    return this->m_jiffiesStats[0];
}

/////////////////////
///  1.2--更新CPU的Jiffies Stat信息
/////////////////////

//  更新编号为cpuid的CPU的jiffies stat信息
struct cpuusage_jiffies_stat *
CpuUsageUtils::UpdateCpuJiffiesStat(unsigned int cpuid)
{
    qDebug( ) <<__FILE__ <<", " <<__LINE__ <<", " <<__func__<<" 未实现" <<endl;

}

//  更新系统中总的CPU jiffies stat信息
struct cpuusage_jiffies_stat *
CpuUsageUtils::UpdateTotalCpuJiffiesStat( )
{
    qDebug( ) <<__FILE__ <<", " <<__LINE__ <<", " <<__func__<<" 未实现" <<endl;

}

//  更新所有的cpu和总的jiffies stat信息
/// 对象创建时将数据更新到m_jiffiesStats和m_prevJiffiesStats
///
/// 每次更新时
/// *   清除老旧的m_prevJiffiesStats数据
/// *   将原来的jiffies Stats的数据保存到m_prevJiffiesStats
/// *   将数据更新到m_jiffiesStats
///     以上是UpdateAllCpusJiffiesStat函数的工作
/// *   同时计算负载信息m_cpuusage即m_jiffiesStats和m_prevJiffiesStats的差值
cpuusage_jiffies_stat_list
CpuUsageUtils::UpdateAllCpusJiffiesStat( )
{
    //  清除老旧的m_prevJiffiesStats数据
    this->UninitPrevCpusJiffiesStat( );
    //  将原来的jiffies Stats的数据保存到m_prevJiffiesStats
    //this->m_prevJiffiesStats = this->m_jiffiesStats;
    this->CopyJiffiesStatsToPre( );

    //  将数据更新到m_jiffiesStats
    this->InitAllCpusJiffiesStat( );
}



///////////////////////////////////////////////////////////////////
/// 2--CPU usage的操作接口
///////////////////////////////////////////////////////////////////

/////////////////////
///  2.1--获取CPU的Jiffies Stat信息
/////////////////////
double CpuUsageUtils::GetCpuUsage(unsigned int cpuid)
{
    return this->m_cpuusgae[cpuid];
}


double CpuUsageUtils::GetTotalCpuUsage( )
{
    return this->m_cpuusgae[this->m_cpunums];
}



QList<double> CpuUsageUtils::GetAllCpusUsage( )
{
    return this->m_cpuusgae;
}


/////////////////////
///  2.2--更新CPU的usage信息
/////////////////////
double CpuUsageUtils::UpdateCpuUsage(unsigned int cpuid)
{
    qDebug( ) <<__FILE__ <<", " <<__LINE__ <<", " <<__func__<<" 未实现" <<endl;
}

double CpuUsageUtils::UpdateTotalCpuUsage( )
{
    qDebug( ) <<__FILE__ <<", " <<__LINE__ <<", " <<__func__<<" 未实现" <<endl;

}

//  更新所有的cpu和总的jiffies stat信息
/// 对象创建时将数据更新到m_jiffiesStats和m_prevJiffiesStats
///
/// 每次更新时
/// *   清除老旧的m_prevJiffiesStats数据
/// *   将原来的jiffies Stats的数据保存到m_prevJiffiesStats
/// *   将数据更新到m_jiffiesStats
///     以上是UpdateAllCpusJiffiesStat函数的工作
/// *   同时计算负载信息m_cpuusage即m_jiffiesStats和m_prevJiffiesStats的差值
///     以上是UpdateAllCpusUsage( )函数的工作
QList<double> CpuUsageUtils::UpdateAllCpusUsage( )
{
    // 清除旧的cpuusage信息
    if(this->m_cpuusgae.size( ) > 0)
    {
        this->m_cpuusgae.clear( );
    }
    // 更新cpu jiffies stat信息
    this->UpdateAllCpusJiffiesStat( );
    //  重新计算负载数据
    return this->CalcAllCpusUsage( );
}
