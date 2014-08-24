#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <include/core.h>
#include <include/messaging.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "private.h"

int CreateMessageQueue(const char *name, int mode)
{
	int key;
	int queue;

	if ((name == NULL) || (strlen(name) <= 0))
		return -EINVAL;

	if ((key = (int)CRC32(0L, (void*)name, strlen(name))) == 0)
		return -EINVAL;

	if ((queue = msgget((key_t)key, IPC_CREAT|mode)) < 0)
		return -errno;

	return queue;
}

int OpenMessageQueue(const char *name)
{
	int key;
	int queue;

	if ((name == NULL) || (strlen(name) <= 0))
		return -EINVAL;

	if ((key = (int)CRC32(0L, (void*)name, strlen(name))) == 0)
		return -EINVAL;

	if ((queue = msgget((key_t)key, 0)) < 0)
		return -errno;

	return queue;
}

int GetMessageQueueUserID(int queue)
{
	if ((queue < 0)) {
		return -1;
	}

	struct msqid_ds msg_data;
	if (msgctl(queue, IPC_STAT, &msg_data) == -1) {
		return -1;
	}

	return (int)msg_data.msg_perm.cuid;
}

int GetMessageQueueCount(int queue)
{
	if ((queue < 0))
	{
		return -1;
	}

	struct msqid_ds msg_data;
	if (msgctl(queue, IPC_STAT, &msg_data) == -1)
	{
		return -1;
	}

	return (int)msg_data.msg_qnum;
}


