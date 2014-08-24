#include <stdio.h>
#include <string.h>
#include "private.h"

#ifndef override
#define override __attribute__((weak))
#endif

/* View Events */
#define VIEW_INIT                 1
#define VIEW_CREATE               2
#define VIEW_SHOW                 3
#define VIEW_HIDE                 4
#define VIEW_MOVE                 5
#define VIEW_RESIZE               6
#define VIEW_DESTROY              7
#define VIEW_SWAP                 8
#define VIEW_BEGINDRAG            9

/* ViewCreate event. */
int override ViewCreate(int id, int type)
{
	return 0;
}


/* Pointer event. */
int override DispatchView(const TASKMSG *msg)
{
	RETURN_IF_NULL(msg);
	int cmd = msg->data1;
	switch (cmd) {
	case VIEW_CREATE: return ViewCreate(msg->data2, msg->data3);
//	case POINTER_DOWN: return MouseDown(msg->data2, msg->data3, msg->data4);
//	case POINTER_MOVE: return MouseMove(msg->data2, msg->data3, msg->data4);
//	case POINTER_WHEEL: return MouseWheel(msg->data2, msg->data3, msg->data4);
	}
	return 0;
}

