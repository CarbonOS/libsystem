#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <asm/fcntl.h>
#include <asm/unistd.h>
#include <linux/limits.h>
#include "private.h"
#include "kernel.h"
#include "io.h"

#ifndef KERNEL_CMDLINE
#define KERNEL_CMDLINE PROCESS_TREE "/cmdline"
#endif

static inline const char *SkipNext(const char *string, char value)
{
	if (!string) {
		return NULL;
	}
	while (string[0]) {
		if (string[0] == value) {
			string++;
			break;
		}
		string++;
	}
	if (strlen(string) <= 0) {
		return NULL;
	}
	return string;
}

static inline char* __GetBootParam(const char *data, const char *name)
{
	if (strncasecmp(data, name, strlen(name))) {
		return NULL;
	}

	const char *next = NULL;
	if (!(next = SkipNext(data, '='))) {
		return NULL;
	}

	return strdup(next);
}


static int GetBootCommandline(char *string, unsigned int length)
{
	int handle = -1;
	if ((handle = OpenFile(KERNEL_CMDLINE, (O_RDONLY), 0)) < 0) {
		return 0;
	}
	if ((Read(handle, string, length) <= 0)) {
		CloseFile(handle);
		return 0;
	}
	CloseFile(handle);
	return 1;
}

const char* GetBootParameter(const char *name)
{
	if ((!name) || (strlen(name) <= 0)) {
		return NULL;
	}

	char cmdline[PATH_MAX];
	memset(cmdline, 0, PATH_MAX);
	if (!GetBootCommandline(cmdline, PATH_MAX)) {
		return NULL;
	}

	char *data = NULL;
	char *item = NULL;
	char *save = cmdline;
	while ((data = strsep(&save, " "))) {
		if (strlen(data) <= 0) {
			continue;
		}
		if ((item = __GetBootParam(data, name))) {
			return item;
		}
	}

	return NULL;
}

int GetRootVolumeUUID(UUID *uuid)
{
	RETURN_IF_NULL(uuid);
	const char* data = NULL;
	if (!(data = GetBootParameter("root"))) {
		return 0;
	}

	if (strncasecmp(data, "UUID=", 5)) {
		free((void*)data);
		return 0;
	}

	const char *next = (data + 5);
	if (!ParseUUID(next, uuid)) {
		free((void*)data);
		return 0;
	}

	free((void*)data);
	return 1;
}





