#include <stdio.h>
#include <asm/unistd.h>
#include <include/core.h>
#include <include/user.h>
#include "private.h"

/* The GetUserID function */
/* returns the real user ID */
/* of the current process. */
UID GetUserID(void)
{
	UID uid = -1;
	if ((uid = ISyscall(__NR_getuid)) < 0){
		return -1;
	}
	return uid;
}

/* The SetCurrentUserID function */
/* sets the effective user ID of the */
/* current process. If the effective UID of */
/* the caller is root, the real UID and */
/* saved set-user-ID are also set. */
int SetCurrentUserID(UID uid)
{
	int result = -1;
	if ((result = ISyscall(__NR_setuid, uid)) < 0) {
		return -1;
	}
	return result;
}

