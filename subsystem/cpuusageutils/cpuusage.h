/*
 *  cpuusage.h - definitions for libcpufreq
 *
 *  Copyright (C) 2004-2009  Dominik Brodowski <linux@dominikbrodowski.de>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 2 of the License.
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


// http://lxr.free-electrons.com/source/Documentation/filesystems/proc.txt
// http://blog.csdn.net/stormbjm/article/details/19202849
typedef struct cpustat
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
};



#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

#endif /* _cpuusage_H */
