#include <stddef.h>
#include <asm/stat.h>
#include <asm/fcntl.h>
#include <asm/unistd.h>
#include "private.h"
#include "device.h"

DEVICEID CreateDeviceID(int major, int minor)
{
	if ((major < 0) || (minor < 0))
	{
		return 0;
	}

	return (    (((major) & 0xfffU) << 8)  |  ((minor) & 0xffU)  |  (((minor) & 0xfff00U) << 12)   );
}

/* Creates a I/O device file. */
int CreateDeviceFile(const char *filename, DEVICEID device, unsigned int mode)
{
	if ((filename == NULL) || (device == 0))
	{
		return 0;
	}

#ifdef __NR_mknod

	int result;
	if ((result = IntSyscall(__NR_mknod, filename, mode, device)))
	{
		printf("__NR_mknod [%d]\n", result);
		return 0;
	}
	return 1;

#else
	return 0;
#endif
}

/*  */
int GetDeviceFromFile(const char *filename)
{
	struct stat64 stat;

#ifdef __NR_stat64

	if (IntSyscall(__NR_stat64, filename, &stat))
	{
		return -1;
	}

	return (int)(stat.st_rdev);
#else
	return -1;
#endif
}

