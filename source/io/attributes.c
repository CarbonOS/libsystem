#include <stddef.h>
#include <asm/fcntl.h>
#include <asm/unistd.h>
#include <linux/xattr.h>
#include "private.h"
#include "io.h"

/* Sets the attributes for a file or directory. */
int SetFileAttribute(const char *filename, const char *name, const void *value, unsigned int length)
{
	if ((filename == NULL) || (name == NULL))
	{
		return 0;
	}

	int result = 0;
	if ((result = ISyscall(__NR_lsetxattr, filename, name, value, length, 0))) {
		printf("result:%d\n", result);
		return 0;
	}

	return 1;
}

/* Retrieves file system attributes for a specified file or directory. */
int GetFileAttribute(const char *filename, const char *name, void *value, unsigned int length)
{
	if ((filename == NULL) || (name == NULL))
	{
		return 0;
	}

#ifdef __NR_lgetxattr

	if (IntSyscall(__NR_lgetxattr, filename, name, value, length, 0))
	{
		return 0;
	}

	return 1;

#else
#error "No [lgetxattr] syscall"
#endif
}


int SetFileAttributeInt32(const char *filename, const char *name, int value)
{
	char data[32];

	if ((filename == NULL) || (name == NULL))
	{
		return 0;
	}

	snprintf(data, sizeof(data), "%d", value);
	if (!SetFileAttribute(filename, name, (void*)data, sizeof(data))) {
		return 0;
	}

	return 1;
}

int GetFileAttributeInt32(const char *filename, const char *name)
{
	char data[32];

	return 0;
}

