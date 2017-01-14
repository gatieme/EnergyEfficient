/*
 *  cpufreq.h - definitions for libcpufreq
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

#ifndef __HMPSCHED_H_INCLUDE__
#define __HMPSCHED_H_INCLUDE__



typedef struct hmpsched_avg {
	/*
	 * These sums represent an infinite geometric series and so are bound
	 * above by 1024/(1-y).  Thus we only need a unsigned int to store them for for all
	 * choices of y < 1-2^(-32)*1024.
	 */
	unsigned long   runnable_avg_sum, runnable_avg_period;  /* int */
	unsigned long   last_runnable_update;
	signed   long   decay_count;
	unsigned long   load_avg_contrib;
        unsigned long   load_avg_ratio;
#ifdef CONFIG_SCHED_HMP
#ifdef CONFIG_SCHED_HMP_ENHANCEMENT
        unsigned long   pending_load;
        unsigned int    nr_pending;                             /* int */
#ifdef CONFIG_SCHED_HMP_PRIO_FILTER
        unsigned long   nr_dequeuing_low_prio;                  /* int */
        unsigned long    nr_normal_prio;                        /* int */
#endif  /*      CONFIG_SCHED_HMP_PRIO_FILTER    */
#endif  /*      CONFIG_SCHED_HMP_ENHANCEMENT    */
        unsigned long   hmp_last_up_migration;
        unsigned long   hmp_last_down_migration;
#endif  /* CONFIG_SCHED_HMP                     */
        unsigned long   usage_avg_sum;                          /* int */
}hmpsched_avg;




#ifdef __cplusplus
extern "C" {
#endif



/*
 * returns 0 if the specified CPU is present,
 * and an error value if not.
 */
struct hmpsched_avg* hmpsched_get_task_avg(unsigned int cpu);
struct hmpsched_avg* hmpsched_set_task_avg(unsigned int cpu);
void hmpsched_put_task_avg(unsigned int cpu);



void hmpsched_get_XXX(unsigned int cpu);



/*
 * returns 0 if the specified CPU is present,
 * and an error value if not.
 */
extern int hmpsched_task_exists(unsigned int cpu);


#ifdef __cplusplus
}
#endif

#endif /* _CPUFREQ_H */
