#include <stdio.h>
#include <include/core.h>
#include <include/task.h>
#include <signal.h>

static int task_func(void* arg)
{
	TASKMSG msg;
	printf("taskid: %d\n", GetCurrentTaskID());

	//TaskSetMask(TASK_MASK_CALL);

	while (1)
	{

//		printf("pid: %d\n", GetMessage(&msg));
		if (TaskWaitMessage(&msg, 500) < 0)
			continue;


		printf("task-msg: %d\n", msg.type);
		printf("param1: %d\n", msg.data1);
		printf("param2: %d\n", msg.data2);
		printf("param3: %d\n", msg.data3);
		printf("param4: %d\n", msg.data4);
		printf("extra: %s\n", (char*)msg.extra);
	}

	//printf("task...\n");
	return 0;
}

int main (int argc, char *argv[])
{
	HTASK task1;
	int i = 0;
//	TaskUnsetMask(TASK_MASK_CALL);

	if (!(task1 = CreateTask(task_func, NULL)))
	{
		printf("CreateTask() failed!\n");
		return -1;
	}

	printf("id: %d\n", GetTaskID(task1));

	TASKMSG msg;
	TASKMSG msg2;

	msg2.type = 256;
	msg2.data1 = 0;
	while ((msg.type != 000)) {

		printf("wait: %d\n", TaskWaitMessage(&msg, 1000));


		msg2.type = 4000;
		msg2.data1 = 1000; 
		msg2.data2 = 2000; 
		msg2.data3 = 3000; 
		msg2.data4 = 4000; 
		sprintf((char*)msg2.extra, "Hello Message Extra [%d] Data!", i++);
		//printf("sendmsg\n");
		TaskSendMessage(GetTaskID(task1), (TASKMSG*)&msg2);
	}

	return 0;
}

