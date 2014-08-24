#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <linux/types.h>
#include <linux/limits.h>
#include <include/core.h>
#include <include/process.h>
#include "private.h"

/* Locals */
static char pbuffer[PATH_MAX];

#define PROCESS_PATH "/proc"
/*
int EnumProcesses(int index, Process *pprocess)
{
	if ((index < 0) || (pprocess == NULL))
	{
		return 0;
	}

	int handle = -1;
	memset(pbuffer, 0, PATH_MAX);
	sprintf(pbuffer, "%s/%d/status", PROCESS_PATH, index);
	if ((handle = open(pbuffer, O_RDONLY)) < 0)
	{
		return 0;
	}

	close(handle);
	return 1;
}
*/
