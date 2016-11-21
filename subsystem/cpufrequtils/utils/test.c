/*************************************************************************
    > File Name: test.c
    > Author: GatieMe
    > Mail: gatieme@163.com
    > Created Time: 2016年11月21日 星期一 15时15分04秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>


#include "cpufreq.h"


int main(void)
{
    int maxcpuid = 4;
    for(int cpuid = 0; cpuid <= maxcpuid; cpuid++)
    {
        if(cpufreq_cpu_exists(cpuid) == 0)
        {
            printf("cpu %d is exists\n", cpuid);

        }
        else
        {
            printf("cpu %d is not exists\n", cpuid);
        }
    }



}

void test_cpu(unsigned int cpuid)
{
    unsigned long scaling_cur_freq = cpufreq_get_freq_kernel(cpuid); // cpufreq_get
    unsigned long cpuinfo_cur_freq = cpufreq_get_freq_hardware(cpuid);
}
