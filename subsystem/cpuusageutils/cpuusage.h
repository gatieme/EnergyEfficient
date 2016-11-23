/*
 *  cpuusage.h - definitions for libcpufreq
 *
 *  Copyright (C) 2016-2017  gatieme <gatieme@163.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 3 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __CPUUSAGE_H_INCLUDE__
#define __CPUUSAGE_H_INCLUDE__

#include "interface.h"

#ifdef __cplusplus
extern "C" {
#endif


// http://lxr.free-electrons.com/source/Documentation/filesystems/proc.txt
// http://blog.csdn.net/stormbjm/article/details/19202849


///////////////////////////////////////////////////////////////
/// cpuusage_jiffies_stat的接口
///////////////////////////////////////////////////////////////

/////////////////////
/// cpuusage_jiffies_stat的数据结构
/////////////////////
typedef struct cpuusage_jiffies_stat
{
    /*  参数--解析--(单位：jiffies)
     *  总的cpu时间total_cpu_time = user + nice + system + idle + iowait + irq + softirq + stealstolen + guest + guest_nice
     *  */
    char        cpu[6];
    long int    user;       /*  从系统启动开始累计到当前时刻, 处于用户态的运行时间, 不包含 nice值为负进程   */
    long int    nice;       /*  从系统启动开始累计到当前时刻, nice值为负的进程所占用的CPU时间               */
    long int    system;     /*  从系统启动开始累计到当前时刻, 处于核心态的运行时间                          */
    long int    idle;       /*  从系统启动开始累计到当前时刻, 除IO等待时间以外的其它等待时间                */
    long int    iowait;     /*  从系统启动开始累计到当前时刻, IO等待时间(since 2.5.41)                      */
    long int    irq;        /*  从系统启动开始累计到当前时刻, 硬中断时间(since 2.6.0-test4)                 */
    long int    softirq;    /*  从系统启动开始累计到当前时刻, 软中断时间(since 2.6.0-test4)                 */
    long int    steal;      /*  which is the time spent in other operating systems when running in a virtualized environment(since 2.6.11)  */
    long int    guest;      /*  which is the time spent running a virtual  CPU  for  guest operating systems under the control of the Linux kernel(since 2.6.24)    */
    long int    guest_nice; /*  running a niced guest  */
}cpuusage_jiffies_stat;


/////////////////////
/// cpuusage_jiffies_stat的处理函数
/////////////////////

/*  获取cpu的总stat信息             */
extern struct cpuusage_jiffies_stat*
cpuusage_get_total_jiffies_stat( );

/*  获取cpu的stat信息(/proc/stat)   */
extern struct cpuusage_jiffies_stat*
cpuusage_get_cpu_jiffies_stat(unsigned int cpuid);

/*  释放cpuusage_jiffies_stat的空间*/
extern void
cpuusage_put_jiffies_stat(struct cpuusage_jiffies_stat *stat);


/*  获取cpu的使用率                 */
extern double
cpuusage_get_usage(struct cpuusage_jiffies_stat *first, struct cpuusage_jiffies_stat *second);


/*  获取当前cpu的总运行时间         */
#define cpuusage_get_cpu_total_time(pjiffies)            \
    ((pjiffies)->user    + (pjiffies)->nice          +   \
     (pjiffies)->system  + (pjiffies)->idle          +   \
     (pjiffies)->iowait  + (pjiffies)->irq           +   \
     (pjiffies)->softirq + (pjiffies)->steal         +   \
     (pjiffies)->guest   + (pjiffies)->guest_nice)

/*  获取当前cpu的总空闲时间         */
#define cpuusage_get_cpu_idle_time(pjiffies)            \
    ((pjiffies)->idle)


///////////////////////////////////////////////////////////////
/// cpuusage_jiffies_stat_list链表的接口
///////////////////////////////////////////////////////////////

/////////////////////
/// cpuusage_jiffies_stat_list链表的数据结构
/////////////////////
typedef struct cpuusage_jiffies_stat_list
{
    struct cpuusage_jiffies_stat        *jiffies_stat;
    struct cpuusage_jiffies_stat_list   *next;
}cpuusage_jiffies_stat_list;


/*  获取所有cpu的总stat信息并组织成链表             */
extern struct cpuusage_jiffies_stat_list *
cpuusage_get_jiffies_stat_list( );

/*  获取所有cpu的总stat信息并组织成链表             */
extern int
cpuusage_put_jiffies_stat_list( );



#ifdef __cplusplus
}
#endif




#endif /*   #define __CPUUSAGE_H_INCLUDE__    */
