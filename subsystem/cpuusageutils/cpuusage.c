/*
 *  Copyright (C) 2016-2017  gatieme <gatieme@163.com>
 *
 *  Licensed under the terms of the GNU GPL License version 3.
 */


#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "cpuusage.h"


/////////////////////
/// cpuusage_jiffies_stat的处理函数
/////////////////////

/*  获取cpu的总stat信息             */
struct cpuusage_jiffies_stat *
cpuusage_get_total_jiffies_stat( )
{
	struct cpuusage_jiffies_stat *jiffies_stat = NULL;

    jiffies_stat = proc_get_total_jiffies_stat( );

    return jiffies_stat;
}

/*  获取cpu的stat信息(/proc/stat)   */
struct cpuusage_jiffies_stat*
cpuusage_get_cpu_jiffies_stat(unsigned int cpuid)
{
	struct cpuusage_jiffies_stat *jiffies_stat = NULL;

    jiffies_stat = proc_get_cpu_jiffies_stat(cpuid);

    return jiffies_stat;

}

/*  释放cpuusage_jiffies_stat的空间*/
void cpuusage_put_jiffies_stat(struct cpuusage_jiffies_stat *stat)
{
    if(stat != NULL)
    {
        free(stat);
    }
}




/*  获取cpu的使用率                 */
double cpuusage_get_usage(struct cpuusage_jiffies_stat *first, struct cpuusage_jiffies_stat *second)
{
    /*
     * cpu usage=(idle2-idle1)/(cpu2-cpu1)*100
     * cpu usage=[(user_2 +sys_2+nice_2) - (user_1 + sys_1+nice_1)]/(total_2 - total_1)*100
     * */
    unsigned long first_total = cpuusage_get_cpu_total_time(first);
    unsigned long first_idle  = cpuusage_get_cpu_idle_time(first);
    unsigned long second_total = cpuusage_get_cpu_total_time(second);
    unsigned long second_idle = cpuusage_get_cpu_idle_time(second);

    double idle = (double)(second_idle - first_idle) / (second_total - first_total) * 100;
    double usage = 100 - idle;
    printf("cpu total  = %ld\n", second_total - first_total);
    printf("cpu idle   = %ld\n", second_idle - first_idle);
    printf("cpu useage = %.2f%%\n", usage);

    return usage;
}
