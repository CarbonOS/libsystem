#include <stdio.h>
#include <asm/unistd.h>
#include <include/core.h>
#include <include/user.h>
#include "private.h"

/* The GetGroupID function */
/* returns the real group ID */
/* of the calling process. */
GID GetGroupID(void)
{
	GID gid = -1;
	if ((gid = (GID)ISyscall(__NR_getgid32)) < 0)
		return -1;
	return gid;
}

