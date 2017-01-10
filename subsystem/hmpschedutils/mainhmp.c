#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <sys/sysinfo.h>
#include <unistd.h>

#define __DEBUG__ 1

#include "hmpsched.h"


#define CK_TIME 5

int main(int argc ,char *argv[])
{
        readout_proc_hmpsched(1);

        return EXIT_SUCCESS;
}
