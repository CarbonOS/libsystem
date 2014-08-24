#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include "private.h"
#include "events.h"
#include <errno.h>

/* Private Object */
typedef struct __ipipe
{
	IEventObject base;
	char data[1024];
	int fd;

} IPipe;

/* Internal Event Wrapper */
static int IPipeGetEvent(IEventObject *object, EVENT *event, int flags)
{
	IPipe *ipipe = NULL;
	if (!(ipipe = (IPipe*)object)) {
		return 0;
	}

	event->type = EVENT_TIMER;
	event->param1 = (int)ipipe;
	event->param2 = 0;
	return 1;
}

/* Creates an named pipe, and returns the handle. */
int CreateNamedPipe(const char *name, int mode)
{
	int key;
	int handle;
	char filename[PATH_MAX] = { 0 };

	if ((name == NULL) || (strlen(name) <= 0))
		return -EINVAL;

	if ((key = (int)CRC32(0L, (void*)name, strlen(name))) == 0)
		return -EINVAL;

	if (sprintf(filename, "%s/Pipe%d", SYSTEM_TEMP, key) <= 0)
		return -EINVAL;

	if (mknod(filename, (mode | S_IFIFO), 0))
		return -errno;

	if ((handle = open(filename, O_RDWR)) < 0)
		return -errno;

	return handle;
}

/* Open an named pipe, and returns the handle. */
int OpenPipe(const char *name)
{
	int key;
	int handle;
	char filename[PATH_MAX];

	if ((name == NULL) || (strlen(name) <= 0))
		return -EINVAL;

	if ((key = (int)CRC32(0L, (void*)name, strlen(name))) == 0)
		return -EINVAL;

	if (sprintf(filename, "%s/Pipe%d", SYSTEM_TEMP, key) <= 0)
		return -EINVAL;

	if ((handle = open(filename, O_RDWR)) < 0)
		return -errno;

	return handle;
}

/* Summary */
int AddPipeToEventQueue(int queue, int pipe)
{
	if ((queue < 0) || (pipe < 0))
		return -1;

	IDispatch dispatch;
	dispatch.handle = pipe;
	dispatch.events = EPOLLIN;
	dispatch.invoke = GetPipeEvent;
	if (epoll_ctl(queue, EPOLL_CTL_ADD, pipe, (struct epoll_event*)&dispatch))
	{
		return -1;
	}

	return 0;
}

/* Summary */
int AddPipeToEventQueueWithCallback(int queue, int pipe, pfnEventCallback callback)
{
	if ((queue < 0) || (pipe < 0))
		return -1;

	if ((callback == NULL))
		return -1;

	IDispatch dispatch;
	dispatch.handle = pipe;
	dispatch.events = EPOLLIN;
	dispatch.invoke = callback;
	if (epoll_ctl(queue, EPOLL_CTL_ADD, pipe, (struct epoll_event*)&dispatch))
	{
		return -1;
	}

	return 0;
}

/* */
int LockPipe(int handle)
{
	if ((handle < 0))
		return -EINVAL;

	if (flock(handle, LOCK_EX) < 0)
		return -errno;

	return 0;
}

/* */
int UnlockPipe(int handle)
{
	if ((handle < 0))
		return -EINVAL;

	if (flock(handle, LOCK_UN) < 0)
		return -errno;

	return 0;
}











