#include <stdio.h>
#include <stdlib.h>
#include <include/core.h>
#include <include/events.h>
#include <linux/inotify.h>
#include <string.h>

int main (int argc, char *argv[])
{
	int queue;
	int notify;
	int watch;
	Event event = { 0 };

	if ((queue = GetMainEventQueue()) < 0)
	{
		printf("GetMainEventQueue() failed!\n");

		return -1;
	}

	if ((notify = CreateFileNotification()) < 0)
	{
		printf("CreateFileNotification() failed!\n");

		return -1;
	}

	if (AddFileNotifyToEventQueue(queue, notify))
	{
		printf("AddFileNotifyToEventQueue() failed!\n");

		return -1;
	}

	if ((watch = AddFileWatch(notify, "/proc", IN_ACCESS)) < 0)
	{
		printf("AddFileWatch() failed!\n");

		return -1;
	}

	while (event.type != EVENT_ID_QUIT)
	{
		if (DispatchEvent(queue, &event, 1000) <= 0)
		{
			printf("next...\n");
			continue;
		}
		//if (GetEvent(&event) <= 0)
		//	continue;

		printf("Incoming Event[%d]...\n", event.type);
	}

	return 0;
}

