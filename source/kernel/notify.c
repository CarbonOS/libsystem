#include <stdio.h>
#include <asm/unistd.h>
#include "private.h"
#include "notify.h"

#ifndef __NR_tasknotify
#define __NR_tasknotify 371
#endif

int SetTaskNotify(unsigned int mask)
{
	if (ISyscall(__NR_tasknotify, mask)) {
		return 0;
	}
	return 1;
}

