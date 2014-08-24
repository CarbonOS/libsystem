#ifndef __SYSTEM_IO_H__
#define __SYSTEM_IO_H__

#include <stdint.h>

/* SeekFile flags */
#define FILE_SEEK_SET      0
#define FILE_SEEK_CUR      1
#define FILE_SEEK_END      2
#define FILE_SEEK_DATA     3
#define FILE_SEEK_HOLE     4
#define FILE_SEEK_MAX      FILE_SEEK_HOLE

/* LockFile flags */
#define FILE_LOCK_SH       1    /* Shared lock */
#define FILE_LOCK_EX       2    /* Exclusive lock */
#define FILE_LOCK_UN       8    /* Remove lock */


/* MatchFilename flags */
#define FNM_NOMATCH      1     /* Match failed. */
#define FNM_NOSYS        2     /* Function not supported (unused). */
#define FILE_MATCH_NOESCAPE     0x01        /* Disable backslash escaping. */
#define FILE_MATCH_PATHNAME     0x02        /* Slash must be matched by slash. */
#define FILE_MATCH_PERIOD       0x04        /* Period must be matched by period. */
#define FILE_MATCH_LEADING_DIR  0x08        /* Ignore /<tail> after Imatch. */
#define FILE_MATCH_CASEFOLD     0x10        /* Case insensitive search. */
#define FILE_MATCH_IGNORECASE   FILE_MATCH_CASEFOLD
#define FILE_MATCH_FILE_NAME    FILE_MATCH_PATHNAME

/* C++ Interface */
#ifdef __cplusplus
extern "C" {
#endif

/* Object Handle */
typedef struct __handle *HANDLE;

typedef unsigned long long DEVNODE;

/* Creates or opens a file or I/O device. */
int OpenFile(const char *filename, int flags, int mode);

/* Creates or opens a file with exclusive lock. */
int OpenLocked(const char *filename, int flags, int mode);

/* Reads from a specific file descriptor. */
int Read(int handle, void *data, size_t count);

/* Writes to a specific file descriptor. */
int Write(int handle, const void *data, size_t count);

/* Moves the file pointer of the specified file. */
int SeekFile(int handle, unsigned long offset, unsigned int whence);

/* Apply an advisory lock on an open file. */
int LockFile(int handle, int operation);

/* Remove an advisory lock on an open file. */
int UnlockFile(int handle);

/* Sends a control code directly to a specified device file descriptor. */
int IoControl(int handle, unsigned int cmd, const void *arg);

int IOControlWait(int handle, unsigned int cmd, const void *arg);

/* Retrieves the size of the specified file, in bytes. */
unsigned int GetFileSize(int handle);

/* Retrieves the Device Node of the containing file. */
DEVNODE GetDeviceNodeFromPath(const char *pathname);


unsigned char* GetFileContent(const char *filename);

/* Checks whether a file or directory exists. */
int FileExists(const char *filename);

/* Close a file descriptor. */
int CloseFile(int handle);




/* Sets the attributes for a file or directory. */
int SetFileAttribute(const char *filename, const char *name, const void *value, unsigned int length);

/* Retrieves file system attributes for a specified file or directory. */
int GetFileAttribute(const char *filename, const char *name, void *value, unsigned int length);




/* Creates a symbolic link. */
int CreateSymbolicLink(const char *name, const char *filename);

/* Creates a symbolic link. (VARARGS) */
int CreateSymbolicLinkPath(const char *name, const char *path, ...);

/* Creates a hard link between an existing file and a new file. */
int CreateHardLink(const char *name, const char *filename);

int CreateFileHash(const char *filename, unsigned char hash[16]);


/* Directory Object handle */
typedef struct IDirectory *HDIRECTORY;

/* Opens a directory stream. */
HDIRECTORY OpenDirectory(const char *filename);
HDIRECTORY OpenDirectoryPath(const char *path, ...);
HDIRECTORY OpenSubDirectory(HDIRECTORY parent, const char *pathname);

/* Returns a pointer to the next directory entry in the directory stream. */
const char* ReadDirectory(HDIRECTORY dir);

const char* MatchDirectory(HDIRECTORY dir, const char *pattern);
const char* GetDirectoryEntry(HDIRECTORY dir);


int OpenDirectoryItem(HDIRECTORY dir, const char *pathname, int flags);

/* Resets the position of the directory stream. */
int ResetDirectory(HDIRECTORY dir);

/* Apply an advisory lock on an open file. */
int LockDirectory(HDIRECTORY dir, int operation);

/* Remove an advisory lock on an open file. */
int UnlockDirectory(HDIRECTORY dir);

/* Close a directory stream. */
int CloseDirectory(HDIRECTORY dir);


/* Change the current directory. */
int ChangeDir(const char *pathname);






/* Match a filename or a pathname. */
int MatchFilename(const char *pattern, const char *string, int flags);




int Mount(const char *device, const char *directory, const char *filesystem, unsigned long flags, const void *data);

int Unmount(const char *name, int flags);

void *MapMemoryWithAddress(unsigned long addr, unsigned long length,
			unsigned long prot, unsigned long flags,
			unsigned long fd, uint64_t pgoff);


void *MapMemory(unsigned long length,
		unsigned long prot, unsigned long flags,
		unsigned long fd, unsigned long pgoff);

void *MapMemory64(unsigned long length,
		unsigned long prot, unsigned long flags,
		unsigned long fd, uint64_t pgoff);

int UnmapMemory(void *address, unsigned long length);

#ifdef __cplusplus
}
#endif
#endif
