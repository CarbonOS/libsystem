#include <stdio.h>
#include <string.h>
#include "private.h"

#ifndef override
#define override __attribute__((weak))
#endif

extern int override DispatchView(const TASKMSG *msg);
extern int override DispatchPointer(const TASKMSG *msg);

int override DispatchDefault(const TASKMSG *msg)
{
	return 0;
}

int DispatchMsg(const TASKMSG *msg)
{
	RETURN_IF_NULL(msg);
	switch (msg->type) {
	case TASKMSG_VIEW: return DispatchView(msg);
	case TASKMSG_POINTER: return DispatchPointer(msg);
	default: return DispatchDefault(msg);
	}

	return 0;
}

