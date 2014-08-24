#include <stdio.h>
#include <include/core.h>
#include <include/task.h>
#include <sched.h>

unsigned char stack[4096];

extern int TaskClone(void *stack, int *tid, int *fence, int (*fn)(void*), void *arg);

static int task_func(void* arg)
{

}

static int AsyncEntry(void* arg)
{
	printf("Hello\n");
	return 0;
}

int main (int argc, char *argv[])
{

	memset(stack, 0, 4096);

	printf("Parent [%d]\n", getpid());

	int tid = 0;
	int fence = 0;

	printf("res: %d\n", TaskClone((stack + 4096), &tid, &fence, task_func, NULL));


	CreateAsync(AsyncEntry, NULL);

	sleep(4);

	printf("tid 1: %d\n", tid);
	printf("fence 1: %d\n", fence);
	printf("Parent [%d]\n", getpid());


	while (__sync_val_compare_and_swap(&fence, 0, 1) == 1) {

	}

	printf("sync: %d\n", __sync_val_compare_and_swap(&fence, 1, 0));

	printf("sync2: %d\n", fence);

	return 0;
}

