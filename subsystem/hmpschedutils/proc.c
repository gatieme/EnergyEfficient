/*
 *  (C) 2004  Dominik Brodowski <linux@dominikbrodowski.de>
 *
 *  Licensed under the terms of the GNU GPL License version 2.
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "hmpsched.h"

#define MAX_LINE_LEN 255



#define PROC_TASK               "/proc/%d"

/* http://www.cnblogs.com/GoodGoodWorkDayDayUp/archive/2011/05/27/2059685.html */
#define PROC_TASK_SCHED_FILE         PROC_TASK"/sched"
#define PROC_TASK_STATM_FILE         PROC_TASK"/statm"
#define PROC_TASK_STAT_FILE          PROC_TASK"/stat"   /* statstruct_proc */
#define PROC_TASK_status

#define HMP_SCHED_PROC_LOAD_WEIGHT_SHIFT        38
#define HMP_SCHED_PROC_SCHED_AVG_SHIFT          39
#define HMP_SCHED_PROC_SCHED_AVG_SIZE           13
#define HMP_SCHED_PROC_SCHED_AVG_END            \
        (HMP_SCHED_PROC_SCHED_AVG_SHIFT + HMP_SCHED_PROC_SCHED_AVG_SIZE)
#define HMP_SCHED_PROC_POLICY_SHIFT             53
#define HMP_SCHED_PROC_PRIORITY_SHIFT           54




/* read access to files which contain one numeric value */
enum HMP_SCHED_AVG{
        RUNNABLE_AVG_SUM = 0,
        RUNNABLE_AVG_PERIOD,
        LAST_RUNNABLE_UPDATE,
        DECAY_COUNT,
        LOAD_AVG_CONTRIB,
        LOAD_AVG_RATIO = 5,

#ifdef CONFIG_SCHED_HMP
#ifdef CONFIG_SCHED_HMP_ENHANCEMENT
        PENDING_LOAD = 6,
        NR_PENDING = 7,
#ifdef CONFIG_SCHED_HMP_PRIO_FILTER
        NR_DEQUEUING_LOW_PRIO = 8,
        NR_NORMAL_PRIO = 9,
#endif
        HMP_LAST_UP_MIGRATION = 10,
        HMP_LAST_DOWN_MIGRATION = 11,
#endif
        USAGE_AVG_SUM = 12,
#endif
        NR_HMP_SCHED_AVG = 13,
};

static const char *value_line[NR_HMP_SCHED_AVG] = {
	[RUNNABLE_AVG_SUM]              = "runnable_avg_sum",
	[RUNNABLE_AVG_PERIOD]           = "runnable_avg_period",
	[LAST_RUNNABLE_UPDATE]          = "last_runnable_update",
	[DECAY_COUNT]                   = "decay_count",
	[LOAD_AVG_CONTRIB]              = "load_avg_contrib",
	[LOAD_AVG_RATIO]                = "load_avg_ratio",
#ifdef CONFIG_SCHED_HMP
#ifdef CONFIG_SCHED_HMP_ENHANCEMENT
	[PENDING_LOAD]                  = "scaling_max_freq",
	[NR_PENDING]                    = "stats/total_trans"
#ifdef CONFIG_SCHED_HMP_PRIO_FILTER
        [NR_DEQUEUING_LOW_PRIO]         = "nr_dequeuing_low_prio",
        [NR_NORMAL_PRIO]                = "nr_normal_prio",
#endif
        [HMP_LAST_UP_MIGRATION]         = "hmp_last_up_migration",
        [HMP_LAST_DOWN_MIGRATION]       = "hmp_last_down_migration",
#endif
        [USAGE_AVG_SUM]                 = "usage_avg_sum",
#endif
};

int readout_proc_hmpsched(
                unsigned int pid,
                struct hmpsched_avg *avg)
{
	FILE *fp = NULL;
	char filename[MAX_LINE_LEN];
	char line[MAX_LINE_LEN];
        char value_name[MAX_LINE_LEN];
        long value_data;
	int ret = -ENODEV;
        int offset = 0;

        snprintf(filename, MAX_LINE_LEN, PROC_TASK_SCHED_FILE, pid);
	fp = fopen(filename, "r");
	if (!fp){
                perror("open error");
		return -ENODEV;
        }
	for(offset = 0; !feof(fp); offset++) {
		if (!fgets(line, MAX_LINE_LEN, fp)) {
			ret = -EIO;
			goto error;
		}

		if (strlen(line) > (MAX_LINE_LEN - 10)) {
			ret = -EIO;
			goto error;
		}

                if(offset < HMP_SCHED_PROC_SCHED_AVG_SHIFT)
                {
                        continue;
                }

		ret = sscanf(line, "%s : %ld", value_name, &value_data);
		if (ret != 2) {
			ret = -EIO;
			goto error;
		}
                printf("%s", line);
                printf("%-45s:%21ld\n", value_name, value_data);
	        memcpy(avg + offset - HMP_SCHED_PROC_SCHED_AVG_SHIFT,
                       &value_data,
                       sizeof(unsigned long));
                printf("%ld == %ld\n",
                                value_data,
                                *(avg + offset - HMP_SCHED_PROC_SCHED_AVG_SHIFT));
        }
        ret = 0;
 error:
	fclose(fp);
	return (ret);
}

extern int proc_task_exists(unsigned int pid) {
	int ret;
        struct hmpsched_avg avg;
	ret = readout_proc_hmpsched(pid, &avg);
	if (ret)
		return -ENODEV;

	return 0;
}

extern int proc_get_task_hmpsched_avg(unsigned int pid) {

        return 0;
}
