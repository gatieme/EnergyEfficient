/*
 *  interface.h - definitions for libcpufreq
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

#ifndef __INTERFACE_H_INCLUDE__
#define __INTERFACE_H_INCLUDE__

#define INTERFACE_PROC  1

#ifdef __cplusplus
extern "C" {
#endif


// http://lxr.free-electrons.com/source/Documentation/filesystems/proc.txt
// http://blog.csdn.net/stormbjm/article/details/19202849


#ifdef INTERFACE_PROC


/////////////////////
/// cpuusage_jiffies_stat的处理函数
/////////////////////

/*  获取cpu的总stat信息             */
extern struct cpuusage_jiffies_stat*
proc_get_total_jiffies_stat( );

/*  获取cpu的stat信息(/proc/stat)   */
extern struct cpuusage_jiffies_stat*
proc_get_cpu_jiffies_stat(unsigned int cpuid);



/*  获取所有cpu的总stat信息并组织成链表             */
extern struct cpuusage_jiffies_stat_list *
proc_get_total_jiffies_stat_list( );

#endif

#ifdef INTERFACE_SYSFS


#endif


#ifdef __cplusplus
}
#endif




#endif /*   #define __CPUUSAGE_H_INCLUDE__    */
