#include <stdio.h>
#include <asm/unistd.h>
#include <include/core.h>
#include <include/process.h>
#include "private.h"

/* Returns the Thread ID of */
/* the current thread. */
TID GetThreadID(void)
{
	TID tid = -1;
	if ((tid = (TID)ISyscall(__NR_gettid)) < 0) {
		return -1;
	}
	return tid;
}

/* */
TID WaitThread(TID tid)
{
	int status = 0;
	if (ISyscall(__NR_wait4, (int)tid, (int)&status, 0, 0) < 0)
		return -1;
	return tid;
}

