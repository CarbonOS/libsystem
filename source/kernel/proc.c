#include <stdio.h>
#include <string.h>
#include <asm/unistd.h>
#include <linux/limits.h>
#include "private.h"
#include "process.h"

#ifndef PROCESS_TREE
#define PROCESS_TREE "/proc"
#endif

const char* GetProcessTreePath(void)
{
	static const char *path = PROCESS_TREE;
	return path;
}

const char* GetProcessExecutable(int pid)
{
	if (pid <= 0) {
		return NULL;
	}

	char buffer[PATH_MAX];
	char filename[PATH_MAX];
	snprintf(filename, PATH_MAX, "%s/%d/exe", PROCESS_TREE, pid);
	if (ISyscall(__NR_readlink, filename, buffer, PATH_MAX) <= 0) {
		return NULL;
	}

	return strdup(buffer);
}

