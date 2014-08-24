#include <stddef.h>
#include <asm/stat.h>
#include <asm/fcntl.h>
#include <asm/unistd.h>
#include <asm/errno.h>
#include "private.h"
#include "io.h"

/* Creates or opens a file or I/O device. */
int OpenFile(const char *filename, int flags, int mode)
{
	flags = (flags <= 0 ? (O_RDONLY|O_CLOEXEC) : flags);
	return (ISyscall(__NR_open, filename, flags, mode));
}

/* Creates or opens a file with exclusive lock. */
int OpenLocked(const char *filename, int flags, int mode)
{
	int handle = -1;
	if ((handle = ISyscall(__NR_open, filename, flags, mode)) < 0) {
		return -1;
	}

	if (ISyscall(__NR_flock, handle, FILE_LOCK_EX)) {
		CloseFile(handle);
		return -1;
	}

	return handle;
}

/* Reads from a specific file descriptor. */
int Read(int handle, void *data, size_t count)
{
	return (ISyscall(__NR_read, handle, data, count));
}

/* Writes to a specific file descriptor. */
int Write(int handle, const void *data, size_t count)
{
	return (ISyscall(__NR_write, handle, data, count));
}

/* Moves the file pointer of the specified file. */
int SeekFile(int handle, unsigned long offset, unsigned int whence)
{
	int result;
	if ((result = ISyscall(__NR_lseek, handle, offset, whence)) < 0) {
		return -1;
	}
	return result;
}

/* Apply an advisory lock on an open file. */
int LockFile(int handle, int operation)
{
	int result;
	if ((result = ISyscall(__NR_flock, handle, operation))) {
		return -1;
	}
	return result;
}

/* Remove an advisory lock on an open file. */
int UnlockFile(int handle)
{
	int result;
	if ((result = ISyscall(__NR_flock, handle, FILE_LOCK_UN))) {
		return -1;
	}
	return result;
}

/* Sends a control code directly to a specified device file descriptor. */
int IoControl(int handle, unsigned int cmd, const void *arg)
{
	return (ISyscall(__NR_ioctl, handle, cmd, arg));
}

int IOControlWait(int handle, unsigned int cmd, const void *arg)
{
	int result = 0;
	do {
		result = ISyscall(__NR_ioctl, handle, cmd, arg);
	} while ((result == -EINTR) || (result == -EAGAIN));
	return result;
}

/* Retrieves the size of the specified file, in bytes. */
unsigned int GetFileSize(int handle)
{
	struct stat64 stat;
	if (ISyscall(__NR_fstat64, handle, &stat)) {
		return -1;
	}
	return (unsigned int)(stat.st_size);
}

/* Retrieves the Device Node of the containing file. */
DEVNODE GetDeviceNodeFromPath(const char *pathname)
{
	struct stat64 stat;
	if (ISyscall(__NR_stat64, pathname, &stat)) {
		return 0;
	}
	return (stat.st_dev);
}

/* Checks whether a file or directory exists. */
int FileExists(const char *filename)
{
	struct stat64 stat;
	if (ISyscall(__NR_stat64, filename, &stat)) {
		return 0;
	}
	return 1;
}

/* Close a file descriptor. */
int CloseFile(int handle)
{
	if (ISyscall(__NR_close, handle)) {
		return 0;
	}
	return 1;
}


