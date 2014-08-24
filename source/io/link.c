#include <stdio.h>
#include <stdarg.h>
#include <asm/fcntl.h>
#include <asm/unistd.h>
#include "private.h"
#include "io.h"

/* Creates a symbolic link. */
int CreateSymbolicLink(const char *name, const char *filename)
{
	if (ISyscall(__NR_symlink, filename, name)) {
		return 0;
	}
	return 1;
}

/* Creates a symbolic link. (VARARGS) */
int CreateSymbolicLinkPath(const char *name, const char *path, ...)
{
	char buffer[4096];
	va_list arg;
	va_start(arg, path);
	vsnprintf(buffer, sizeof(buffer), path, arg);
	va_end(arg);
	return CreateSymbolicLink(name, buffer);
}

/* Creates a hard link between an existing file and a new file. */
int CreateHardLink(const char *name, const char *filename)
{
	return (ISyscall(__NR_link, filename, name));
}

