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

    first_stat = cpuusage_get_total_jiffies_stat( );
    sleep(CK_TIME);
    second_stat = cpuusage_get_total_jiffies_stat( );
    cpuusage_get_usage(first_stat, second_stat);

    for(unsigned int id = 0; id < cpunum; id++)
    {
        first_stat = cpuusage_get_cpu_jiffies_stat(id);
        sleep(CK_TIME);
        second_stat = cpuusage_get_cpu_jiffies_stat(id);
        cpuusage_get_usage(first_stat, second_stat);

    }

    return EXIT_SUCCESS;
}
