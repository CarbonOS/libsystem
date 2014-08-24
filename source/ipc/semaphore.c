#include <unistd.h>
#include <string.h>
#include <asm/unistd.h>
#include <linux/ipc.h>
#include <linux/shm.h>
#include "private.h"
#include "core.h"

int CreateSemaphore(const char *name, int rights)
{
	int key;
	int handle = -1;
	if ((name == NULL) || (strlen(name) <= 0)) {
		return -1;
	}

	if ((key = (int)CRC32(0L, (void*)name, strlen(name))) == 0) {
		return -1;
	}

#ifdef __NR_ipc
	if ((handle = ISyscall(__NR_ipc, SEMGET, key, 1, (IPC_CREAT|IPC_EXCL|rights))) < 0) {
		return -1;
	}
#endif

	return handle;
}

int OpenSemaphore(const char *name)
{
	int key;
	int handle = -1;
	if ((name == NULL) || (strlen(name) <= 0))
	{
		return -1;
	}

	if ((key = (int)CRC32(0L, (void*)name, strlen(name))) == 0)
	{
		return -1;
	}

#ifdef __NR_ipc
	if ((handle = ISyscall(__NR_ipc, SEMGET, key, 1, 0)) < 0)
		return -1;
#endif

	return handle;
}

