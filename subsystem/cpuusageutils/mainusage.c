#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <sys/sysinfo.h>
#include <unistd.h>

#define __DEBUG__ 1

#include "cpuusage.h"


#define CK_TIME 1

int main(int argc ,char *argv[])
{
    unsigned int cpunum = get_nprocs( );

    struct cpuusage_jiffies_stat *first_stat =  NULL;
    struct cpuusage_jiffies_stat *second_stat =  NULL;

    ///
    first_stat = cpuusage_get_total_jiffies_stat( );
    sleep(CK_TIME);
    second_stat = cpuusage_get_total_jiffies_stat( );
    cpuusage_calc_cpu_usage(first_stat, second_stat);

    ///
    cpuusage_get_total_cpu_usage(CK_TIME);

    for(unsigned int cpuid = 0; cpuid < cpunum; cpuid++)
    {
        ///
        first_stat = cpuusage_get_cpu_jiffies_stat(cpuid);
        sleep(CK_TIME);
        second_stat = cpuusage_get_cpu_jiffies_stat(cpuid);
        cpuusage_calc_cpu_usage(first_stat, second_stat);

        ///
        cpuusage_get_cpu_usage(cpuid, CK_TIME);

    }

    return EXIT_SUCCESS;
}
