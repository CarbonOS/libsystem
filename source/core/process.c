#include <stdio.h>
#include <asm/unistd.h>
#include <include/core.h>
#include <include/process.h>
#include "private.h"


/* Summary */
/* Wait for process to change state. */
/*
PID WaitProcess(PID pid)
{
	int status = 0;
	if (IntSyscall(__NR_waitpid, pid, &status, 0) < 0)
		return -1;
	return pid;
}
*/
/* Summary */
int CloseProcess(PID pid)
{
	if (pid < 1)
		return -1;

	if (ISyscall(__NR_kill, pid, 0) < 0)
		return -1;

	return 0;
}
