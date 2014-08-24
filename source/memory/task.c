#include <stdio.h>
#include <asm/stat.h>
#include <asm/unistd.h>
#include <linux/uio.h>
#include "private.h"
#include "memory.h"


int ReadTaskMemory(int pid, unsigned long address, void *buffer, unsigned int length)
{
	int result = 0;
	struct iovec local;
	struct iovec remote;

	RETURN_IF_NULL(buffer);

	local.iov_base = buffer;
	local.iov_len = length;
	remote.iov_base = (void*)address;
	remote.iov_len = length;
	if ((result = ISyscall(__NR_process_vm_readv, pid, &local, 1, &remote, 1, 0)) < 0) {
		printf("error: %d\n", result);
		return 0;
	}

	return 1;
}

int WriteTaskMemory(int pid, unsigned long address, void *buffer, unsigned int length)
{
	int result = 0;
	struct iovec local;
	struct iovec remote;

	RETURN_IF_NULL(buffer);

	local.iov_base = buffer;
	local.iov_len = length;
	remote.iov_base = (void*)address;
	remote.iov_len = length;
	if ((result = ISyscall(__NR_process_vm_writev, pid, &local, 1, &remote, 1, 0)) < 0) {
		printf("error: %d\n", result);
		return 0;
	}

	return 1;
}

