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
#include "proc.h"


unsigned long
proc_get_task_hmpsched_offset(
                unsigned int pid,
                unsigned int offset)
{
	FILE            *fp = NULL;
	char            filename[MAX_LINE_LEN];
	char            line[MAX_LINE_LEN];
        char            value_name[MAX_LINE_LEN];
        unsigned long   value_data;
        unsigned int    index = 0;
        int             ret;
        snprintf(filename, MAX_LINE_LEN, PROC_TASK_SCHED_FILE, pid);
	fp = fopen(filename, "r");
	if (!fp){
                perror("open error");
		return -ENODEV;
        }
	for(index = 0;
            !feof(fp) && index <= offset;
            index++) {
                if (!fgets(line, MAX_LINE_LEN, fp)) {
			ret = -EIO;
			goto error;
	        }

		if (strlen(line) > (MAX_LINE_LEN - 10)) {
			ret = -EIO;
			goto error;
		}

                if(index < HSP_SCHED_AVG_START_OFFSET)
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
        }

 error:
	fclose(fp);
	return ret;
}

int
proc_get_task_hmpskched_avg(
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

                if(offset < HSP_SCHED_AVG_START_OFFSET)
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
	        memcpy((unsigned long*)avg + offset - HSP_SCHED_AVG_START_OFFSET,
                       &value_data,
                       sizeof(unsigned long));
                printf("%ld == %ld\n",
                                value_data,
                                *((unsigned long *)avg + offset - HSP_SCHED_AVG_START_OFFSET));
        }
        ret = 0;
 error:
	fclose(fp);
	return (ret);
}

extern int proc_task_exists(unsigned int pid) {
	int ret;
        struct hmpsched_avg avg;
	ret = proc_get_task_hmpskched_avg(pid, &avg);
	if (ret)
		return -ENODEV;

	return 0;
}
