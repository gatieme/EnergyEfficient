
#ifndef __PROC_H_INCLUDE__
#define __PROC_H_INCLUDE__


#define MAX_LINE_LEN 255



#define PROC_TASK               "/proc/%d"

/* http://www.cnblogs.com/GoodGoodWorkDayDayUp/archive/2011/05/27/2059685.html */
#define PROC_TASK_SCHED_FILE         PROC_TASK"/sched"
#define PROC_TASK_STATM_FILE         PROC_TASK"/statm"
#define PROC_TASK_STAT_FILE          PROC_TASK"/stat"   /* statstruct_proc */
#define PROC_TASK_STATUS_FILE        PROC_TASK"/status"



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

#if 0
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
#endif

//  以下记录信息是字段在/proc/pid/sched的偏移(行号)为标识的
//  HSP -=> HMP_SCHED_PROC
#define HSP_LOAD_WEIGHT_OFFSET                  38

//  hmpsched_avg字段是/proc/pid/sched中部分信息组成的一个结构体
//  记录了调度实体的负载统计信息
//  偏移区间
//      [HSP_SCHED_AVG_START_OFFSET,
//       HSP_SCHED_AVG_END_OFFSET  ]
//  的所有的结构信息
#define HSP_SCHED_AVG_START_OFFSET              39
#define HSP_SCHED_AVG_SIZE                      13
#define HSP_SCHED_AVG_END_OFFSET                \
                (HSP_SCHED_AVG_START_OFFSET + HSP_SCHED_AVG_SIZE)

//  以下是hmpsched_avg中每个字段的偏移信息
#define HSP_RUNNABLE_AVG_SUM_OFFSET             \
                (HSP_SCHED_AVG_START_OFFSET + RUNNABLE_AVG_SUM)
#define HSP_RUNNABLE_AVG_PERIOD_OFFSET          \
                (HSP_SCHED_AVG_START_OFFSET + RUNNABLE_AVG_PERIOD)
#define HSP_LAST_RUNNABLE_UPDATE_OFFSET         \
                (HSP_SCHED_AVG_START_OFFSET + LAST_RUNNABLE_UPDATE)
#define HSP_DECAY_COUNT_OFFSET                  \
                (HSP_SCHED_AVG_START_OFFSET + DECAY_COUNT)

#define HSP_LOAD_AVG_CONTRIB_OFFSET             \
                (HSP_SCHED_AVG_START_OFFSET + DECAY_COUNT)
#define HSP_LOAD_AVG_RATIO_OFFSET               \
                (HSP_SCHED_AVG_START_OFFSET + LOAD_AVG_RATIO)

#ifdef CONFIG_SCHED_HMP
#ifdef CONFIG_SCHED_HMP_ENHANCEMENT
#define HSP_PENDING_LOAD_OFFSET                 \
                (HSP_SCHED_AVG_START_OFFSET + PENDING_LOAD)
#define HSP_NR_PENDING_OFFSET                   \
                (HSP_SCHED_AVG_START_OFFSET + NR_PENDING)

#ifdef CONFIG_SCHED_HMP_PRIO_FILTER

#define HSP_NR_DEQUEUING_LOW_PRIO_OFFSET        \
                (HSP_SCHED_AVG_START_OFFSET + NR_DEQUEUING_LOW_PRIO)
#define HSP_NR_NORMAL_PRIO_OFFSET               \
                (HSP_SCHED_AVG_START_OFFSET + NR_NORMAL_PRIO)
#endif
#define HSP_HMP_LAST_UP_MIGRATION_OFFSET        \
                (HSP_SCHED_AVG_START_OFFSET + HMP_LAST_UP_MIGRATION)
#define HSP_HMP_LAST_DOWN_MIGRATION_OFFSET      \
                (HSP_SCHED_AVG_START_OFFSET + HMP_LAST_DOWN_MIGRATION )

#endif
#define HSP_USAGE_AVG_SUM_OFFSET            \
                (HSP_SCHED_AVG_START_OFFSET + USAGE_AVG_SUM)
#endif


#define HSP_SCHED_POLICY_OFFSET                 53
#define HSP_SCHED_PRIO_OFFSET                   54



#endif
