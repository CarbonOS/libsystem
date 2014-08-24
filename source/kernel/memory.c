#include <stdio.h>
#include <string.h>
#include <asm/stat.h>
#include <asm/unistd.h>
#include <linux/sysinfo.h>
#include "private.h"
#include "kernel.h"

#define PAGEALIGN(size) ((size + (PAGE_SIZE-1)) & ~(PAGE_SIZE-1))

unsigned long GetTotalMemory(void)
{
	struct sysinfo info;
	memset(&info, 0, sizeof(info));
	if (ISyscall(__NR_sysinfo, &info)) {
		return 0;
	}
	return (unsigned long)(info.totalram);
}

unsigned long GetAvailableMemory(void)
{
	struct sysinfo info;
	memset(&info, 0, sizeof(info));
	if (ISyscall(__NR_sysinfo, &info)) {
		return 0;
	}
	return (unsigned long)(info.freeram);
}
