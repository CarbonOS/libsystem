#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <signal.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <string.h>
#include <sched.h>
#include "memory.h"
#include "task.h"
#include "private.h"
#include <errno.h>

/* Task Size */
#ifndef TASK_STACK
#define TASK_STACK (1024*64)
#endif

/* Task Stack Offset */
#ifndef TASK_STACK_OFFSET
#define TASK_STACK_OFFSET(stack) (stack + TASK_STACK)
#endif

/* Private Object */
typedef struct ITask
{
	int tid;
	void *arg;
	TASKFUNC func;
	void *stack;

} *HTASK;

/* Task Proc */
static int TaskProc(void *handle)
{
	struct ITask *task = NULL;
	if (!(task = (struct ITask*)handle) || !(task->func)) {
		return 0;
	}
	return (task->func(task->arg));
}

extern int TaskEntry(int (*fn)(void*), void* arg)
{
	printf("TaskEntry [%d]\n", ISyscall(__NR_gettid));
	sleep(1);

	ISyscall(__NR_exit, 0);

	return 0;
}

/* Creates a new Task. (Thread) */
HTASK CreateTask(TASKFUNC func, void *arg)
{
	struct ITask *task = NULL;
	if (!(task = calloc(1, sizeof(struct ITask)))) {
		return NULL;
	}

	if (!(task->stack = VirtualMalloc(TASK_STACK/*, protection*/)))
	{
		printf("VirtualAlloc failed!\n");
		free(task);
		return NULL;
	}

	task->arg = arg;
	task->func = func;
	int flags = (CLONE_FILES|CLONE_FS|CLONE_VM|CLONE_SIGHAND|CLONE_THREAD|CLONE_SYSVSEM|CLONE_PARENT_SETTID);
	if (clone(TaskProc, TASK_STACK_OFFSET(task->stack), flags, (void*)task, &task->tid, NULL, &task->tid) < 0)
	{
		printf("CreateTask failed!\n");
		VirtualFree(task->stack/*, TASK_STACK*/);
		free(task);
		return NULL;
	}

	return (task);
}

int WaitTask(HTASK handle)
{
	struct ITask *task = NULL;
	if (!(task = (struct ITask*)handle)) {
		return -1;
	}

	int status = 0;
	int option = WUNTRACED;
	if (waitpid(task->tid, &status, option) < 0) {
		printf("WaitTask failed [%d]\n", task->tid);
		return -1;
	}

	return status;
}

int GetTaskID(HTASK handle)
{
	RETURN_IF_NULL(handle);
	return (handle->tid);
}

/* Returns the caller's task ID. */
int GetCurrentTaskID(void)
{
	int taskid = -1;
	taskid = ISyscall(__NR_gettid);
	return taskid;
}

int CloseTask(HTASK handle)
{
	RETURN_IF_NULL(handle);
	if (ISyscall(__NR_tkill, (handle->tid), SIGKILL)) {
		printf("tkill error\n");
	}
	VirtualFree(handle->stack/*, TASK_STACK*/);
	free(handle);
	return 1;
}

