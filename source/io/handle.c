#include <stddef.h>
#include <asm/stat.h>
#include <asm/fcntl.h>
#include <asm/unistd.h>
#include <asm/errno.h>
#include "private.h"
#include "io.h"

void* GetFileHandle(const char *pathname)
{
	RETURN_IF_NULL(pathname);


	return (void*)1;
}

