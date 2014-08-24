#include <stdio.h>
#include <include/task.h>
#include <include/notify.h>

int main (int argc, char *argv[])
{
	if (!SetTaskNotify(NOTIFY_PROCESS)) {
		printf("SetTaskNotify failed!\n");
	}

	TASKMSG msg;
	memset(&msg, 0, sizeof(msg));
	while ((msg.type != TASKMSG_EXIT))
	{
		if (TaskWaitMessage(&msg, 100) < 0) {
			//continue;
		}

		printf("msg: %d\n", msg.type);
		continue;
	}

	return 0;
}




