#include <stdio.h>
#include <stdlib.h>
#include <asm/stat.h>
#include <asm/unistd.h>
#include "private.h"
#include "task.h"

/* Async Data */
typedef struct IAsync
{
	int tid;
	unsigned char stack[4096];

} *HASYNC;

int StartAsyncFunc(void *stack, int *tid, int *fence, int (*fn)(void*), void *arg);

extern int AsyncFuncEntry(int (*entry)(void*), void* arg)
{
	if (!entry) {
		return 0;
	}
	entry(arg);
	return 0;
}

HASYNC CreateAsync(int (*fn)(void*), void *arg)
{
	struct IAsync *async = NULL;
	if (!(async = (struct IAsync*)calloc(1, sizeof(struct IAsync)))) {
		return NULL;
	}

	unsigned char *stack = (async->stack + 4096);
	if (StartAsyncFunc(stack, &async->tid, NULL, fn, arg) <= 0) {
		free(async);
		return NULL;
	}

	return (async);
}

