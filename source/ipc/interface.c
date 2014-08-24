#include <stdio.h>
#include <string.h>
#include "private.h"
#include "task.h"

#ifndef __NR_servicectl
#define __NR_servicectl 368
#endif

static inline int GetInterfaceHash(const char *hash)
{
	int key = 0;
	if ((!hash) || (strlen(hash) <= 0)) {
		return 0;
	}
	if ((key = (int)CRC32(0L, (void*)hash, strlen(hash))) == 0) {
		return 0;
	}
	return (key);
}

int RegisterInterface(const char *hash)
{
	int key = 0;
	if ((key = GetInterfaceHash(hash)) == 0) {
		return 0;
	}
	if (ISyscall(__NR_servicectl, 0, &key)) {
		return 0;
	}
	return 1;
}

int RegisterInterfaceWithHash(unsigned int hash)
{
	if (ISyscall(__NR_servicectl, 0, &hash)) {
		return 0;
	}
	return 1;
}

int GetInterfacePID(const char *hash)
{
	int key = 0;
	if ((key = GetInterfaceHash(hash)) == 0) {
		return 0;
	}
	return ISyscall(__NR_servicectl, 1, &key);
}


