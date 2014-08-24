#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/un.h>
#include "private.h"
#include "channel.h"
#include "socket.h"
#include "events.h"

/* Internal Channel Wrapper */
static int GetChannelEvent(int handle, int flags, void *pEvent)
{
	Event *event;
	if ((event = (Event*)pEvent) == NULL) {
		return -1;
	}

	event->type = EVENT_ID_CHANNEL;
	event->param1 = (int)handle;
	event->param2 = (int)flags;
	event->param3 = (int)0;
	event->param4 = (int)0;
	event->param5 = (int)0;
	return 0;
}

/* Creates a new Channel for a specific service. */
int CreateChannel(const char *path)
{
	int channel;
	struct sockaddr_un addr;
	addr.sun_family = AF_LOCAL;
	channel = socket(PF_LOCAL, SOCK_STREAM|SOCK_CLOEXEC, 0);
	if ((channel < 0))
	{
		return -1;
	}

	strncpy(addr.sun_path, path, UNIX_PATH_MAX);
	if (bind(channel, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		close(channel);
		return -1;
	}

	if (listen(channel, 10) < 0) {
		close(channel);
		return -1;
	}

	return channel;
}

/* Open a Channel for a specific service. */
int OpenChannel(const char *path)
{
	int channel;
	struct sockaddr_un addr;
	addr.sun_family = AF_LOCAL;
	channel = socket(PF_LOCAL, SOCK_STREAM|SOCK_CLOEXEC, 0);
	if ((channel < 0))
	{
		return -1;
	}

	strncpy(addr.sun_path, path, UNIX_PATH_MAX);
	if (Connect(channel, (struct sockaddr*)&addr, sizeof(addr)) < 0)
	{
		close(channel);
		return -1;
	}

	return channel;
}

/* Open a Channel for a specific service. */
int GetChannelConnection(int channel)
{
	int handle;
	socklen_t length;
	struct sockaddr_un addr;
	length = sizeof(addr);
	handle = accept(channel, (struct sockaddr*)&addr, &length/*, SOCK_CLOEXEC*/);
	if ((handle < 0)) {
		return -1;
	}

	return handle;
}

/* Get the Process ID of the specific Channel. */
int GetChannelPID(int channel)
{
	socklen_t length;
	struct ucred ucred;
	length = sizeof(ucred);
	if (getsockopt(channel, SOL_SOCKET, SO_PEERCRED, &ucred, &length)) {
		return -1;
	}

	return (int)ucred.pid;
}

/* Writes to and reads from the channel. */
int CallChannel(int channel, const void *in, size_t in_count, void *out, size_t out_count)
{
	if ((channel < 0) || (in == NULL) || (out == NULL))
	{
		return 0;
	}

	if (write(channel, in, in_count) != in_count)
	{
		return 0;
	}

	if (read(channel, out, out_count) != out_count)
	{
		return 0;
	}

	return 1;
}

/* Summary */
int AddChannelToEventQueue(HQUEUE queue, int channel)
{
	if ((queue < 0) || (channel == -1))
	{
		return -1;
	}

	IDispatch dispatch;
	dispatch.handle = channel;
	dispatch.events = EPOLLIN;
	dispatch.invoke = GetChannelEvent;
	if (epoll_ctl(queue, EPOLL_CTL_ADD, channel, (struct epoll_event*)&dispatch))
	{
		return -1;
	}

	return 0;
}

/* Summary */
/* Close the Channel object. */
int CloseChannel(int channel)
{
	if ((channel < 0))
	{
		return -1;
	}

	close(channel);
	return 0;
}

