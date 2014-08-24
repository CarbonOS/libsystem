#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <asm/fcntl.h>
#include <asm/unistd.h>
#include "private.h"
#include "io.h"

/* Kernel Internal */
struct KernelEntry
{
	unsigned long	d_ino;
	unsigned long	d_off;
	unsigned short	d_reclen;
	char		d_name[1];
};

/* Kernel Internal */
struct KernelEntry64
{
	uint64_t d_ino;
	int64_t d_off;
	unsigned short d_reclen;
	unsigned char d_type;
	char d_name[1];
};

/* Directory Object data */
typedef struct IDirectory
{
	int handle;
	unsigned long bytes;
	unsigned long offset;
	unsigned char data[1024];
	unsigned char *next;

} *HDIRECTORY;

/* Opens a directory stream. */
int OpenDirectoryInternal(struct IDirectory *data, const char *pathname)
{
	int handle;
	RETURN_IF_NULL(data);
	RETURN_IF_NULL(pathname);
	if ((handle = OpenFile(pathname, (O_RDONLY|O_NDELAY|O_DIRECTORY|O_CLOEXEC), 0)) < 0){
		return 0;
	}

	data->bytes = 0;
	data->offset = 0;
	data->handle = handle;
	return 1;
}

/* Opens a directory stream. */
HDIRECTORY OpenDirectory(const char *pathname)
{
	struct IDirectory *data = NULL;
	if (!(data = (struct IDirectory*)calloc(1, sizeof(struct IDirectory)))) {
		return NULL;
	}

	if (!OpenDirectoryInternal(data, pathname)) {
		free(data);
		return NULL;
	}

	return (data);
}

/* Opens a directory stream. (VARARGS) */
HDIRECTORY OpenDirectoryPath(const char *path, ...)
{
	char buffer[4096];
	va_list arg;
	va_start(arg, path);
	vsnprintf(buffer, sizeof(buffer), path, arg);
	va_end(arg);

	return OpenDirectory(buffer);
}

/* Opens a Sub Directory stream. */
HDIRECTORY OpenSubDirectory(HDIRECTORY parent, const char *pathname)
{
	int handle;
	RETURN_IF_NULL(parent);
	if ((handle = ISyscall(__NR_openat, (parent->handle), pathname, (O_RDONLY|O_NDELAY|O_DIRECTORY|O_CLOEXEC), 0)) < 0) {
		return NULL;
	}

	struct IDirectory *data = NULL;
	if (!(data = (struct IDirectory*)calloc(1, sizeof(struct IDirectory)))) {
		CloseFile(handle);
		return NULL;
	}

	data->bytes = 0;
	data->offset = 0;
	data->handle = handle;
	return (data);
}

/* Internal Function */
static inline int FillDirectory(struct IDirectory *dir)
{
	int bytes = 0;
	if ((bytes = ISyscall(__NR_getdents64, dir->handle, dir->data, sizeof(dir->data))) <= 0) {
		return 0;
	}
	dir->offset = 0;
	dir->next = dir->data;
	dir->bytes = bytes;
	return 1;
}

/* Returns a pointer to the next directory entry in the directory stream. */
const char* ReadDirectory(HDIRECTORY dir)
{
	RETURN_IF_NULL(dir);
	if ((dir->bytes <= 0) && (!FillDirectory(dir))) {
		return NULL;
	}

	struct KernelEntry64 *entry;
	if (!(entry = (struct KernelEntry64*)dir->next)) {
		return NULL;
	}

	const char *string = (entry->d_name);
	dir->next = (dir->next + entry->d_reclen);
	dir->bytes -= entry->d_reclen;
	return (string);
}

const char* GetDirectoryEntry(HDIRECTORY dir)
{
	RETURN_IF_NULL(dir);
	const char *string = NULL;
	while ((string = ReadDirectory(dir))) {
		if (string[0] != '.') {
			return (string);
		}
	}
	return NULL;
}

/* Opens a directory stream. */
int OpenDirectoryItem(HDIRECTORY dir, const char *pathname, int flags)
{
	int handle;
	RETURN_IF_NULL(dir);
	RETURN_IF_NULL(pathname);
	flags = (flags <= 0 ? (O_RDONLY|O_CLOEXEC) : flags);
	if ((handle = ISyscall(__NR_openat, (dir->handle), pathname, flags, 0)) < 0) {
		return -1;
	}
	return (handle);
}

const char* MatchDirectory(HDIRECTORY dir, const char *pattern)
{
	RETURN_IF_NULL(dir);
	RETURN_IF_NULL(pattern);
	const char *string = NULL;
	while ((string = ReadDirectory(dir))) {
		if (!MatchFilename(pattern, string, 0)) {
			return (string);
		}
	}
	return NULL;
}

/* Resets the position of the directory stream. */
int ResetDirectory(HDIRECTORY dir)
{
	RETURN_IF_NULL(dir);
	SeekFile(dir->handle, 0, FILE_SEEK_SET);
	return 1;
}

/* Close a directory stream. */
int CloseDirectory(HDIRECTORY dir)
{
	RETURN_IF_NULL(dir);
	CloseFile(dir->handle);
	free(dir);
	return 1;
}

int CreateDirectory(const char *pathname, int mode)
{
	if (ISyscall(__NR_mkdir, pathname, mode)) {
		return 0;
	}
	return 0;
}

/* Change the current directory. */
int ChangeDir(const char *pathname)
{
	int errno = 0;
	if ((errno = ISyscall(__NR_chdir, pathname))) {
		return 0;
	}
	return 1;
}

