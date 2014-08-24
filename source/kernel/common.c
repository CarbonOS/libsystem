#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <asm/fcntl.h>
#include <asm/unistd.h>
#include <linux/limits.h>
#include "private.h"
#include "kernel.h"
#include "io.h"

#ifndef KERNEL_SYS
#define KERNEL_SYS PROCESS_TREE "/sys/kernel"
#endif

#ifndef KERNEL_MODPROBE
#define KERNEL_MODPROBE KERNEL_SYS "/modprobe"
#endif

#ifndef KERNEL_HOTPLUG
#define KERNEL_HOTPLUG KERNEL_SYS "/hotplug"
#endif

#ifndef KERNEL_POWEROF
#define KERNEL_POWEROF KERNEL_SYS "/poweroff_cmd"
#endif

static int _WriteData(const char *file, const char *content)
{
	if ((!file) || (!content)) {
		return 0;
	}

	int handle = -1;
	if ((handle = OpenLocked(file, (O_WRONLY), 0)) < 0) {
		return 0;
	}

	int bytes = 0;
	bytes = Write(handle, (void*)content, strlen(content));
	CloseFile(handle);
	return (bytes > 0);
}

int SetHotplugHelper(const char *pathname)
{
	return _WriteData(KERNEL_HOTPLUG, pathname);
}

int SetModprobeHelper(const char *pathname)
{
	return _WriteData(KERNEL_MODPROBE, pathname);
}

int SetPowerOfHelper(const char *pathname)
{
	return _WriteData(KERNEL_POWEROF, pathname);
}

int PivotRoot(const char *new, const char *old)
{
	int errno = 0;
	if ((errno = ISyscall(__NR_pivot_root, new, old))) {
		printf("errno: %d\n", errno);
		return 0;
	}
	return 1;
}

