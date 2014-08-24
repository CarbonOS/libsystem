#include <stdio.h>
#include <stdlib.h>
#include <asm/stat.h>
#include <asm/fcntl.h>
#include <asm/unistd.h>
#include "private.h"
#include "mount.h"
#include "core.h"

/* Local Filesystems */
static const char* filesystem[] =
{
	("ext2"),
	("ext3"),
	("ext4"),
	("vfat"),
	("reiserfs"),
	("iso9660"),
	("ntfs"),
	("udf"),
	(NULL)
};

int Mount(const char *device, const char *directory, const char *filesystem, unsigned long flags, const void *data)
{
	int errno = 0;
	RETURN_IF_NULL(directory)
	if ((errno = ISyscall(__NR_mount, device, directory, filesystem, flags, data))) {
		return 0;
	}
	return 1;
}

int AutoMount(const char *device, const char *directory, unsigned long flags)
{
	int index = 0;
	RETURN_IF_NULL(device)
	RETURN_IF_NULL(directory)
	while ((filesystem[index] != NULL)) {
		if (Mount(device, directory, filesystem[index], flags, NULL)) {
			return 1;
		}
		index++;
	}

	return 0;
}

int Unmount(const char *target, int flags)
{
	int errno = 0;
	RETURN_IF_NULL(target)
	if ((errno = ISyscall(__NR_umount, target, flags))) {
		return 0;
	}

	return 1;
}



