#include <string.h>
#include <asm/unistd.h>
#include <linux/time.h>
#include <linux/resource.h>
#include <include/core.h>
#include <include/process.h>
#include "private.h"

int GetProcessorCount(void)
{
/*
	int count;
	if ((count = (int)sysconf(_SC_NPROCESSORS_ONLN)) <= 0)
	{
		return -1;
	}
*/
	return 0;
}

/* Summary */
/* Retrieves the number of the */
/* processor the current thread was running. */
int GetCurrentProcessorNumber(void)
{
	int cpu = -1;
	if (ISyscall(__NR_getcpu, (&cpu), 0, 0) < 0) {
		return -1;
	}
	return cpu;
}

unsigned int GetProcessorTime(void)
{
	struct rusage res;
	memset(&res, 0, sizeof(res));
	if (ISyscall(__NR_getrusage, RUSAGE_SELF, &res)) {
		return -1;
	}
	return (unsigned int)((res.ru_utime.tv_sec * 1000UL) + (res.ru_utime.tv_usec / 1000UL));
}

int SetProcessorMask(int mask)
{
	if ((mask == 0)) {
		return SYS_INVALID_VALUE;
	}

	int size = sizeof(mask);
	if (ISyscall(__NR_sched_setaffinity, 0, size, (int)(&mask)))
		return -1;
	return 0;
}

