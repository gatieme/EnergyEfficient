/*
 *  Copyright (C) 2016-2017  gatieme <gatieme@163.com>
 *
 *  Licensed under the terms of the GNU GPL License version 3.
 */


#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
cpuusage_get_jiffies_stat(unsigned int cpuid)
{
	struct cpuusage_jiffies_stat *jiffies_stat = NULL;

    jiffies_stat = proc_get_jiffies_stat(cpuid);

    return jiffies_stat;
}


/*  获取所有cpu的总stat信息并组织成链表             */
struct cpuusage_jiffies_stat *
cpuusage_get_jiffies_stat_list( )
{
	struct cpuusage_jiffies_stat *jiffies_stat_list = NULL;

    jiffies_stat_list = proc_get_jiffies_stat_list( );

    return jiffies_stat_list;
}



struct cpuusage_jiffies_stat*
cpuusage_set_jiffies_stat(
        const char      *cpu,
        unsigned long   user,       unsigned long   nice,
        unsigned long   system,     unsigned long   idle,
        unsigned long   iowait,     unsigned long   irq,
        unsigned long   softirq,    unsigned long   steal,
        unsigned long   guest,      unsigned long   guest_nice,
        struct cpuusage_jiffies_stat    *next,
        struct cpuusage_jiffies_stat    *first)
{
    struct cpuusage_jiffies_stat    *jiffies_stat = NULL;
    if((jiffies_stat = (struct cpuusage_jiffies_stat *)malloc(sizeof(struct cpuusage_jiffies_stat))) == NULL)
    //if((jiffies_stat = (struct cpuusage_jiffies_stat *)calloc(1, sizeof(struct cpuusage_jiffies_stat))) == NULL)
    {
        perror("malloc");
        exit(-1);
    }

    strcpy(jiffies_stat->cpu, cpu);
    jiffies_stat->user          = user;
    jiffies_stat->nice          = nice;
    jiffies_stat->system        = system;
    jiffies_stat->idle          = idle;
    jiffies_stat->iowait        = iowait;
    jiffies_stat->irq           = irq;
    jiffies_stat->softirq       = softirq;
    jiffies_stat->steal         = steal;
    jiffies_stat->guest         = guest;
    jiffies_stat->guest_nice    = guest_nice;

    jiffies_stat->next      = next;
    jiffies_stat->first     = first;


    return jiffies_stat;
}

#if defined(INLINE)

/*  释放cpuusage_jiffies_stat的空间*/
extern inline void
cpuusage_show_jiffies_stat(struct cpuusage_jiffies_stat *stat)
{
    printf("jiffies-stat : "
           "%s, %ld, %ld, %ld, %ld, %ld, %ld, %ld, %ld, %ld, %ld\n",
            stat->cpu,
            stat->user, stat->nice, stat->system, stat->idle,
            stat->iowait, stat->irq, stat->softirq,
            stat->steal, stat->guest, stat->guest_nice);
}

#endif

/*  释放cpuusage_jiffies_stat的空间*/
extern void
cpuusage_show_jiffies_stat_list(struct cpuusage_jiffies_stat *stat)
{
    if(stat == NULL)
    {
        return;
    }
    struct cpuusage_jiffies_stat* curr_stat = stat->first;
    while(curr_stat != NULL)
    {
        cpuusage_show_jiffies_stat(curr_stat);
        curr_stat = curr_stat->next;
    }
}


#if defined(INLINE)

/*  释放cpuusage_jiffies_stat的空间*/
inline void cpuusage_put_jiffies_stat(struct cpuusage_jiffies_stat *stat)
{
    if(stat != NULL)
    {
        free(stat);
    }
}

#endif

/*  释放cpuusage_jiffies_stat的空间*/
void cpuusage_put_jiffies_stat_list(struct cpuusage_jiffies_stat *stat)
{
    if (stat == NULL)
    {
		return;
    }
    struct cpuusage_jiffies_stat    *curr_stat = stat->first;
    struct cpuusage_jiffies_stat    *next_stat = stat->first;

    while (curr_stat != NULL)
    {
		next_stat = curr_stat->next;
		free(curr_stat);
		curr_stat = next_stat;
	}
}




/*  计算cpu的使用率                 */
double
cpuusage_calc_usage(
        struct cpuusage_jiffies_stat *first,
        struct cpuusage_jiffies_stat *second)
{
    /*
     * cpu usage=(idle2-idle1)/(cpu2-cpu1)*100
     * cpu usage=[(user_2 +sys_2+nice_2) - (user_1 + sys_1+nice_1)]/(total_2 - total_1)*100
     * */
    unsigned long first_total = cpuusage_get_total_time(first);
    unsigned long first_idle  = cpuusage_get_idle_time(first);
    unsigned long second_total = cpuusage_get_total_time(second);
    unsigned long second_idle = cpuusage_get_idle_time(second);
    if (second_total - first_total == 0)
    {
        return 0.0;
    }
    double idle = (double)((long)second_idle - (long)first_idle) / ((long)second_total - (long)first_total) * 100;
    double usage = 100 - idle;
    printf("cpu total  = %ld\n", second_total - first_total);
    printf("cpu idle   = %ld\n", second_idle - first_idle);
    printf("cpu useage = %.2f%%\n", usage);

    return usage;
}



/*  获取当前cpu的使用率                 */
double cpuusage_get_usage(unsigned int cpuid, unsigned int delay)
{
    struct cpuusage_jiffies_stat    *first_stat = NULL;
    struct cpuusage_jiffies_stat    *second_stat = NULL;
    double cpuusage = 0;

    first_stat = cpuusage_get_jiffies_stat(cpuid);
    sleep(delay);
    second_stat = cpuusage_get_jiffies_stat(cpuid);

    cpuusage = cpuusage_calc_usage(first_stat, second_stat);

    return cpuusage;
}


/*  获取系统cpu的使用率                 */
double cpuusage_get_total_usage(unsigned int delay)
{
    struct cpuusage_jiffies_stat    *first_stat = NULL;
    struct cpuusage_jiffies_stat    *second_stat = NULL;
    double cpuusage = 0;

    first_stat = cpuusage_get_total_jiffies_stat( );
    sleep(delay);
    second_stat = cpuusage_get_total_jiffies_stat( );

    cpuusage = cpuusage_calc_usage(first_stat, second_stat);

    return cpuusage;
}

