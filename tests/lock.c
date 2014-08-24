#include <stddef.h>
#include <system/task.h>
#include <system/core.h>
#include <system/lock.h>

static HTASK task1;
static HTASK task2;
static HTASK task3;
static HTASK task4;

static DEFINE_LOCK(mlock) = 0;
static DEFINE_FENCE(mfence) = 0;

static int task_func(void* arg)
{
	while (1)
	{
	//	WaitFence(&mfence);
		CriticalLock(&mlock);
		printf("task-locked: %d\n", *(int*)arg);
		sleep(1);
		CriticalUnlock(&mlock);
	}

	return 0;
}

int main(int argc, char *argv[])
{

	int id1 = 1;
	int id2 = 2;
	int id3 = 3;

	if (!(task1 = CreateTask(task_func, &id1)))
	{
		printf("CreateTask() failed!\n");
		return -1;
	}

	if (!(task2 = CreateTask(task_func, &id2)))
	{
		printf("CreateTask() failed!\n");
		return -1;
	}

	if (!(task3 = CreateTask(task_func, &id3)))
	{
		printf("CreateTask() failed!\n");
		return -1;
	}


	while (1) {

		CriticalLock(&mlock);
		printf("task-locked: %d\n", GetCurrentTaskID());
		sleep(4);
		TriggerFence(&mfence);
		CriticalUnlock(&mlock);
	}

	return 0;
}

