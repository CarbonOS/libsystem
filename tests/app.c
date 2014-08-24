#include <stdio.h>
#include <include/core.h>
#include <include/task.h>
#include <include/messaging.h>
#include <signal.h>

int main (int argc, char *argv[])
{

	TASKMSG msg;

	if (ApplicationRegister("System.Composer")) {
		printf("ApplicationRegister failed: %d\n", 0);
	}

	if (ApplicationRegister("System.Composer")) {
		printf("ApplicationRegister failed: %d\n", 0);
	}

	while ((msg.type != MSG_QUIT)) {

		if (TaskWaitMessage(&msg, 1000) <= 0) {
			printf("wait: %d\n", 0);
		} else {
			printf("msg: %d\n", msg.type);
		}

	}

	return 0;
}

