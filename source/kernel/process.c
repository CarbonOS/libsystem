#include <stdio.h>
#include <unistd.h>
#include <asm/stat.h>
#include <asm/unistd.h>
#include "resource.h"
#include "process.h"
#include "private.h"

/* Returns the process ID */
/* of the calling process. */
int GetProcessID(void)
{
	int pid = -1;
	pid = ISyscall(__NR_getpid);
	return pid;
}

/* Returns the parent process ID */
/* of the calling process. */
int GetParentProcessID(void)
{
	int pid = -1;
	pid = ISyscall(__NR_getppid);
	return pid;
}

/* Returns the process group ID of */
/* the process specified by pid. If pid */
/* is zero, the process ID of the */
/* current process is used. */
PID GetProcessGroupID(PID pid)
{
	PID pgid = -1;
	if ((pgid = ISyscall(__NR_getpgrp, pid)) < 0)
		return -1;
	return pgid;
}

/* The Function creates a new process */
/* by duplicating the calling process. */
PID DuplicateProcess(void)
{
	PID pid = -1;
	if ((pid = ISyscall(__NR_fork)) < 0) {
		return -1;
	}
	return pid;
}


int StartProcessWithEnv(const char *filename, const char * const *commandline, const char * const *environment)
{
	int errno = 0;
	RETURN_IF_NULL(filename);
	RETURN_IF_NULL(commandline);
	RETURN_IF_NULL(environment);
	if ((errno = ISyscall(__NR_execve, filename, commandline, environment))) {
		return 0;
	}
	return 1;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnonnull"
int StartProcess(const char *filename, const char *commandline)
{
	RETURN_IF_NULL(filename);
	RETURN_IF_NULL(commandline);
	const char *envp[] = { NULL };
	const char *argv[] = { filename, commandline, NULL };
	if (!StartProcessWithEnv(filename, argv, __environ)) {
		return 0;
	}
	return 1;
}
#pragma GCC diagnostic pop

PID CreateProcess(const char *filename, const char *commandline)
{
	PID process = 0;
	RETURN_IF_NULL(filename);
	RETURN_IF_NULL(commandline);
	if ((process = DuplicateProcess()) < 0) {
		return -1;
	}
	else if ((process > 0)) { /* parent */
		return (process);
	}
	else if ((process == 0)) { /* child */
		CreateProcess(filename, commandline);
	}

	return -1;

}

/* Wait for process to change state. */
PID WaitProcess(PID pid)
{
	int status = 0;
	if (ISyscall(__NR_waitpid, pid, &status, 0) != pid) {
		return -1;
	}
	return pid;
}

