#include <stdio.h>
#include <string.h>
#include <asm/stat.h>
#include <asm/unistd.h>
#include <linux/capability.h>
#include "private.h"

#ifndef CHECK_FLAG
#define CHECK_FLAG(data, flag) \
(data[CAP_TO_INDEX(flag)] & CAP_TO_MASK(flag))
#endif

int CheckPermission(int flag)
{
	struct __user_cap_header_struct header;
	header.version = _LINUX_CAPABILITY_VERSION_3;
	header.pid = (int)ISyscall(__NR_getpid);

	unsigned int data[3];
	memset(data, 0, sizeof(data));
	if (ISyscall(__NR_capget, &header, &data)) {
		return 0;
	}

	printf("0x%08x\n", data[0]);
	printf("0x%08x\n", data[1]);
	printf("0x%08x\n", data[2]);

	printf("i: %d\n", CAP_TO_INDEX(CAP_BLOCK_SUSPEND));

	return CHECK_FLAG(data, flag);
}

int SetPermission(int flag)
{
	int errno = 0;
	struct __user_cap_header_struct header;
	header.version = _LINUX_CAPABILITY_VERSION_3;
	header.pid = (int)ISyscall(__NR_gettid);

	printf("version: 0x%08x\n", header.version);

	unsigned int data[3];
	memset(data, 0, sizeof(data));
	if (ISyscall(__NR_capget, &header, &data)) {
		printf("capget failed!\n");
		return 0;
	}

	//memset(data, 0, sizeof(data));
	data[CAP_TO_INDEX(flag)] |= CAP_TO_MASK(flag);
	if ((errno = ISyscall(__NR_capset, &header, &data))) {
		printf("capset failed! [%d]\n", errno);
		printf("version: 0x%08x\n", header.version);
		return 0;
	}

	printf("0x%08x\n", data[0]);
	printf("0x%08x\n", data[1]);
	printf("0x%08x\n", data[2]);
	return 1;
}

