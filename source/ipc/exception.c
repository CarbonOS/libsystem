#include <stdio.h>
#include <string.h>
#include "private.h"
#include "trace.h"
#include "task.h"

typedef struct __Trace
{
	int caption_length;

} TRACE_EXTRA;

int TraceException(const char *caption, const char *message)
{
	if (!caption || strlen(caption) <= 0) {
		return 0;
	}
	if (!message || strlen(message) <= 0) {
		return 0;
	}


	return 0;
}


int TraceAssert(const char *expr, const char *file, int line, const char *func)
{
	printf("Trace\n");
	printf("\tFile: %s [%d]\n", file, line);
	printf("\tFunction: %s\n", func);
	printf("\tExpression: (%s)\n", expr);
	return 0;
}



