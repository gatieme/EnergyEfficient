/*
 *  (C) 2004  Dominik Brodowski <linux@dominikbrodowski.de>
 *
 *  Licensed under the terms of the GNU GPL License version 2.
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <fcntl.h>
#include <unistd.h>


#define __DEBUG__   1
#include "cpuusage.h"

#define MAX_LINE_LEN 255
#define PROC_STAT_FILE "/proc/stat"



/*  获取所有cpu的总stat信息并组织成链表             */
struct cpuusage_jiffies_stat_list *
proc_get_jiffies_stat_list( )
{
    unsigned int cpunums = get_nprocs( );
    FILE *fp = NULL;
    char buf[128];
    char cpu[6];
    long int user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    //long int total_jiffies_stat;
    struct cpuusage_jiffies_stat    *jiffies_stat = NULL;

    fp = fopen(PROC_STAT_FILE, "r");
    if(fp == NULL)
    {
        perror("fopen ");
        exit (0);
    }

	for(unsigned int id = 0;
        id <=  (cpunums + 1) && !feof(fp);
        id++)
    {
		if (!fgets(buf, sizeof(buf), fp))
        {
			goto error;
		}

		if (strlen(buf) > (MAX_LINE_LEN - 10))
        {
			goto error;
		}
#if __DEBUG__
        printf("buf=%s",buf);
#endif
        sscanf(buf,"%s%ld%ld%ld%ld%ld%ld%ld%ld%ld%ld",
                cpu, &user, &nice, &system, &idle, &iowait,
                &irq, &softirq, &steal, &guest, &guest_nice);

#if __DEBUG__
        printf("%s, %ld, %ld, %ld, %ld, %ld, %ld, %ld, %ld, %ld, %ld\n",
            cpu, user, nice, system, idle, iowait,
            irq, softirq, steal, guest, guest_nice);
#endif
        fclose(fp);
    }
    if((jiffies_stat = (struct cpuusage_jiffies_stat *)malloc(sizeof(struct cpuusage_jiffies_stat))) == NULL)
    {
        perror("malloc");
        exit(-1);
    }
    strcpy(jiffies_stat->cpu, cpu);
    jiffies_stat->user      = user;
    jiffies_stat->nice      = nice;
    jiffies_stat->system    = system;
    jiffies_stat->idle      = idle;
    jiffies_stat->iowait    = iowait;
    jiffies_stat->irq       = irq;
    jiffies_stat->softirq   = softirq;
    jiffies_stat->steal     = steal;
    jiffies_stat->guest     = guest;
    jiffies_stat->guest     = guest_nice;

	return jiffies_stat;
error:
	fclose(fp);
	return NULL;
}





/////////////////////
/// cpuusage_jiffies_stat的处理函数
/////////////////////

/*  获取cpu的总stat信息             */
struct cpuusage_jiffies_stat *
proc_get_total_jiffies_stat( )
{
    FILE *fp = NULL;
    char buf[128];
    char cpu[6];
    long int user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    //long int total_jiffies_stat;
    struct cpuusage_jiffies_stat    *jiffies_stat = NULL;

    fp = fopen(PROC_STAT_FILE, "r");
    if(fp == NULL)
    {
        perror("fopen:");
        exit (0);
    }
	if (!fgets(buf, sizeof(buf), fp))
    {
		goto error;
	}

	if (strlen(buf) > (MAX_LINE_LEN - 10))
    {
		goto error;
    }

    {
#if __DEBUG__
        printf("buf=%s",buf);
#endif
        sscanf(buf,"%s%ld%ld%ld%ld%ld%ld%ld%ld%ld%ld",
                cpu, &user, &nice, &system, &idle, &iowait,
                &irq, &softirq, &steal, &guest, &guest_nice);

#if __DEBUG__
        printf("%s, %ld, %ld, %ld, %ld, %ld, %ld, %ld, %ld, %ld, %ld\n",
            cpu, user, nice, system, idle, iowait,
            irq, softirq, steal, guest, guest_nice);
#endif

    }
    //total_jiffies_stat = user + nice + system + idle + iowait + irq + softirq + steal + guest + guest_nice;
    fclose(fp);

    if((jiffies_stat = (struct cpuusage_jiffies_stat *)malloc(sizeof(struct cpuusage_jiffies_stat))) == NULL)
    {
        perror("malloc");
        exit(-1);
    }
    strcpy(jiffies_stat->cpu, cpu);
    jiffies_stat->user      = user;
    jiffies_stat->nice      = nice;
    jiffies_stat->system    = system;
    jiffies_stat->idle      = idle;
    jiffies_stat->iowait    = iowait;
    jiffies_stat->irq       = irq;
    jiffies_stat->softirq   = softirq;
    jiffies_stat->steal     = steal;
    jiffies_stat->guest     = guest;
    jiffies_stat->guest     = guest_nice;

    return jiffies_stat;
error:
	fclose(fp);
	return NULL;
}





/*  获取cpu的stat信息(/proc/stat)   */
struct cpuusage_jiffies_stat *
proc_get_cpu_jiffies_stat(unsigned int cpuid)
{
    FILE *fp = NULL;
    char buf[128];
    char cpu[6];
    long int user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    //long int total_jiffies_stat;
    struct cpuusage_jiffies_stat    *jiffies_stat = NULL;

    fp = fopen(PROC_STAT_FILE, "r");
    if(fp == NULL)
    {
        perror("fopen:");
        exit (0);
    }
	if (!fgets(buf, sizeof(buf), fp))
    {
		goto error;
	}

	if (strlen(buf) > (MAX_LINE_LEN - 10))
    {
		goto error;
    }

#if USE_LSEEK

    if (lseek(fp, offset, SEEK_CUR) == (off_t)-1)
    {
        perror("lseek failed");
        return -1;
    }
    else
    {
#else
	for(unsigned int id = 0;
        id <= cpuid && !feof(fp);
        id++)
    {
		if (!fgets(buf, sizeof(buf), fp))
        {
			goto error;
		}

		if (strlen(buf) > (MAX_LINE_LEN - 10))
        {
			goto error;
		}
#if 0   //__DEBUG__
        printf("id = %d, offset = %d\n", id, cpuid);
#endif
        if(id != cpuid)
        {
            continue;
        }
#endif
#if __DEBUG__
        printf("buf=%s",buf);
#endif
        sscanf(buf,"%s%ld%ld%ld%ld%ld%ld%ld%ld%ld%ld",
                cpu, &user, &nice, &system, &idle, &iowait,
                &irq, &softirq, &steal, &guest, &guest_nice);

#if __DEBUG__
        printf("%s, %ld, %ld, %ld, %ld, %ld, %ld, %ld, %ld, %ld, %ld\n",
            cpu, user, nice, system, idle, iowait,
            irq, softirq, steal, guest, guest_nice);
#endif

    }

    //total_jiffies_stat = user + nice + system + idle + iowait + irq + softirq + steal + guest + guest_nice;
    fclose(fp);

    if((jiffies_stat = (struct cpuusage_jiffies_stat *)malloc(sizeof(struct cpuusage_jiffies_stat))) == NULL)
    {
        perror("malloc");
        exit(-1);
    }
    strcpy(jiffies_stat->cpu, cpu);
    jiffies_stat->user      = user;
    jiffies_stat->nice      = nice;
    jiffies_stat->system    = system;
    jiffies_stat->idle      = idle;
    jiffies_stat->iowait    = iowait;
    jiffies_stat->irq       = irq;
    jiffies_stat->softirq   = softirq;
    jiffies_stat->steal     = steal;
    jiffies_stat->guest     = guest;
    jiffies_stat->guest     = guest_nice;

    return jiffies_stat;

error:
	fclose(fp);
	return NULL;
}



