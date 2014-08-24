#include <stdio.h>
#include <string.h>
#include <include/task.h>
#include <include/notify.h>

int main (int argc, char *argv[])
{
	if (!SetTaskNotify(NOTIFY_POINTER)) {
		printf("SetTaskNotify failed!\n");
	}

	TASKMSG msg;
	memset(&msg, 0, sizeof(msg));
	while ((msg.type != TASKMSG_EXIT)) {

		if (TaskWaitMessage(&msg, 1000) < 0) {
			continue;
		}

		if (msg.type == TASKMSG_POINTER) {

			printf("code: %d\n", msg.code);
			printf("bus: %d\n", msg.data1);


		}

		continue;
	}

	return 0;
}
