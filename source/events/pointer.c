#include <stdio.h>
#include <string.h>
#include "private.h"

#ifndef override
#define override __attribute__((weak))
#endif

#define POINTER_UP 1
#define POINTER_DOWN 2
#define POINTER_WHEEL 3
#define POINTER_MOVE 4

/* MouseDown event. */
int override MouseDown(int x, int y, int button)
{
	return 0;
}

/* MouseDown event. */
int override MouseMove(int x, int y, int button)
{
	return 0;
}

/* MouseDown event. */
int override MouseUp(int x, int y, int button)
{
	return 0;
}

/* MouseDown event. */
int override MouseWheel(int x, int y, int button)
{
	return 0;
}


/* Pointer event. */
int override DispatchPointer(const TASKMSG *msg)
{
	RETURN_IF_NULL(msg);
	int cmd = msg->data1;
	switch (cmd) {
	case POINTER_UP: return MouseUp(msg->data2, msg->data3, msg->data4);
	case POINTER_DOWN: return MouseDown(msg->data2, msg->data3, msg->data4);
	case POINTER_MOVE: return MouseMove(msg->data2, msg->data3, msg->data4);
	case POINTER_WHEEL: return MouseWheel(msg->data2, msg->data3, msg->data4);
	}
	return 0;
}

